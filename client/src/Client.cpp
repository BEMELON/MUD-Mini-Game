//
// Created by BEMELON on 22. 12. 5.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "../header/Client.h"
#include "../header/JsonBuilder.h"
#include <iostream>
#include <unistd.h>
#include <regex>

Client::Client(int port, Logger *logger) {
    this->port = port;
    this->logger = logger;
}

int Client::connect() {
    struct sockaddr_in server;

    if ((this->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        this->logger->logSysErrorMsg("Socket Error");

    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(this->port);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (::connect(this->fd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) < 0)
        this->logger->logSysErrorMsg("Connect Error");

    return 1;
}

bool Client::send(std::string msg) {
    char buffer[2048];

    ::memset(buffer, 0, 2048);
    strcpy(buffer, msg.c_str());
    if (::send(this->fd, buffer, 2048, 0) < 0)
        this->logger->logSysErrorMsg("Send Error");

    rapidjson::Document document;
    memset(buffer, 0, 2048);
    if (recv(this->fd, buffer, 2048, 0) < 0)
        this->logger->logSysErrorMsg("Recv Error");

    this->jsonParser.parse(buffer);

    if (this->jsonParser.hasError() || this->jsonParser.getString("status") == "fail") {
        this->logger->logInfoMsg("Json Parse Error");
        return false;
    }

    free(this->user);
    this->user = jsonParser.getUser("user");

    return true;
}

void Client::start() {
    string id;

    this->logger->logInfoMsg("Enter your id");
    getline(cin, id, '\n');
    bool success = this->login(id);

    if (!success) {
        this->logger->logInfoMsg("Login failed.");
        exit (EXIT_FAILURE);
    }
}

bool Client::login(string userId) {
    JsonBuilder builder;
    builder
        .add("Request URL", "/user/login")
        .add("userId", userId);
    bool success = send(builder.build());
    if (!success)
        return false;

    free(this->user);
    this->user = this->jsonParser.getUser("user");
    this->logger->logInfoMsg("Hello, " + this->user->getId());

    printUser();
    return true;
}

void Client::updateUserInfo() {
    free(this->user);
    this->user = this->jsonParser.getUser("user");
}

void Client::printUserCoordinate() {
    char msg[1048];

    ::memset(msg, 0, 1048);
    ::sprintf(msg, "You are at [%d, %d]", user->getX(), user->getY());
    this->logger->logInfoMsg(msg);
}

void Client::printUserHp() {
    char msg[1048];

    ::memset(msg, 0, 1048);
    ::sprintf(msg, "\tHP : %d", user->getHp());
    this->logger->logInfoMsg(msg);
}

void Client::printUserStr() {
    char msg[1048];

    ::memset(msg, 0, 1048);
    ::sprintf(msg, "\tSTR : %d", user->getStr());
    this->logger->logInfoMsg(msg);
}

void Client::printUserPotions() {
    char msg[1048];

    ::memset(msg, 0, 1048);
    ::sprintf(msg, "\tHP_Potion : %d", user->getHpPotions());
    this->logger->logInfoMsg(msg);

    ::memset(msg, 0, 1048);
    ::sprintf(msg, "\tSTR_Potion : %d", user->getStrPotions());
    this->logger->logInfoMsg(msg);
}

bool Client::getCmd() {
    string cmd;

    this->logger->logInfoMsg("Enter your Command (help, move, potion, attack, status, msg, quit)");
    getline(cin, cmd, '\n');
    if (regex_match(cmd, regex("quit"))) {
        this->logger->logInfoMsg("Game terminated.");
        return false;
    } else if (regex_match(cmd, regex("help"))) {
        this->logger->logInfoMsg("\tmove {x} {y} : move x, y");
        this->logger->logInfoMsg("\tpotion {hp|str} {cnt} : use {cnt} {hp|str} potion");
        this->logger->logInfoMsg("\tattack : attack [-1][-1] ~ [1][1]");
        this->logger->logInfoMsg("\tstatus : User status");
        this->logger->logInfoMsg("\tmsg {user-id} {msg} : Send {msg} to {user-id}");
        this->logger->logInfoMsg("\tquit : quit game");
    } else if (regex_match(cmd, regex("move.*"))) {
        move(cmd);
    } else if (regex_match(cmd, regex("potion.*"))) {
        potion(cmd);
    } else if (regex_match(cmd, regex("attack"))) {
        attack();
    } else if (regex_match(cmd, regex("status"))) {
        status();
    } else if (regex_match(cmd, regex("msg.*"))) {
        sendMsg(cmd);
    } else {
        this->logger->logInfoMsg("Wrong command : " + cmd);
    }

    return true;
}

void Client::move(string cmd) {
    int first_space = cmd.find(' ', 0);
    int second_space = cmd.find(' ', first_space + 1);

    int x = stoi(cmd.substr(first_space + 1, second_space));
    int y = stoi(cmd.substr(second_space));

    JsonBuilder builder;
    builder
        .add("Request URL", "/user/" + user->getId() + "/move")
        .add("x", to_string(x))
        .add("y", to_string(y));

    send(builder.build());

    printUser();
}

void Client::potion(string cmd) {
    int first_space = cmd.find(' ', 0);

    string potion_type = cmd.substr(first_space + 1);

    JsonBuilder builder;
    builder
        .add("Request URL", "/user/" + user->getId() + "/potion")
        .add("type", potion_type);
    send(builder.build());

    printUser();
}

void Client::attack() {
    JsonBuilder builder;
    builder
            .add("Request URL", "/user/" + user->getId() + "/attack");
    send(builder.build());

    printUser();
}

void Client::status() {
    JsonBuilder builder;
    builder
            .add("Request URL", "/user/" + user->getId() + "/event");
    send(builder.build());

    printUser();
    printMessages();
}

void Client::sendMsg(string cmd) {
    int first_space = cmd.find(' ', 0);
    int second_space = cmd.find(' ', first_space + 1);

    string to = cmd.substr(first_space + 1, second_space - first_space - 1);
    string content = cmd.substr(second_space + 1);

    JsonBuilder builder;
    builder
            .add("Request URL", "/user/" + user->getId() + "/sendMsg")
            .add("msg_to", to)
            .add("msg_content", content);
    send(builder.build());

    printUser();
}

void Client::printUser() {
    printUserCoordinate();
    printUserHp();
    printUserStr();
    printUserPotions();
}

void Client::close() {
    ::close(this->fd);
}

void Client::printMessages() {
    if (this->user->getMessages().empty())
        return ;
    this->logger->logInfoMsg("You have Messages ..");
    for(string msg: this->user->getMessages()) {
        this->logger->logInfoMsg("\t\t" + msg);
    }
}

void Client::getMessage() {
    JsonBuilder builder;
    builder
            .add("Request URL", "/user/" + user->getId() + "/event");
    send(builder.build());

    printMessages();
}
