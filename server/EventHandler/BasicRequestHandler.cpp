//
// Created by BEMELON on 22. 12. 5.
//

#include <netinet/in.h>
#include <bits/socket.h>
#include <arpa/inet.h>
#include <csignal>
#include <iostream>
#include <hash_map>
#include "../header/BasicRequestHandler.h"

void BasicRequestHandler::listen(int port) {
    // Setup for Logging
    this->logger->logHeader();
    this->logger->logInfoMsg("Server started at port " + std::to_string(port));
    this->port = port;

    struct sockaddr_in server_addr, client_addr; // 서버/클라이언트 구조체
    int passive_fd, active_fd; // Passive / Active 소켓
    socklen_t client_len = 0; // Socket len (ignored)
    rapidjson::Document document; // JSON parser

    char buffer[MAX_BUFFER]; // Buffer space for input
    char msg[MSG_BUFFER]; // msg space for logger

    pid_t pid; // pid for multi-processing

    memset((struct sockaddr *)&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    if ((passive_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        this->logger->logSysErrorMsg("Sock Error");

    if ((bind(passive_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))) < 0)
        this->logger->logSysErrorMsg("Bind Error");

    if (::listen(passive_fd, 30) < 0)
        this->logger->logSysErrorMsg("Listen Error");

    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    this->logger->logInfoMsg("Request Handler boot successful!");


    if ((active_fd = accept(passive_fd, (struct sockaddr *)&client_addr, &client_len)) < 0)
        this->logger->logSysErrorMsg("Accept Error");

    sprintf(msg, "[%d] Process forked !", getpid());
    this->logger->logInfoMsg(msg);

    if (read(active_fd, buffer, MAX_BUFFER) < 0)
        this->logger->logSysErrorMsg("Read failed");

    memset(msg, 0, MSG_BUFFER);
    sprintf(msg, "[CLIENT] %s", buffer);
    this->logger->logInfoMsg(msg);

    document.Parse(buffer);

    if (document.HasParseError())
        this->logger->logInfoMsg("JSON Parsing Error");
    std::cout << document["status"].GetString() << std::endl;

    auto fn = this->router.find("/")->second;
    IController *controller = this->controller.find("/")->second;

    auto res = (controller->*fn)(&document);

    char ack[MAX_BUFFER] = R"({ "status" : "ok" })";
    if (send(active_fd, ack, MAX_BUFFER, 0) < 0)
        this->logger->logSysErrorMsg("Send Error");
}

void BasicRequestHandler::addRoute(std::string path, rapidjson::Document* (IController::*fn_router)(rapidjson::Document *), IController *caller) {
    this->router.insert(std::make_pair(path, fn_router));
    this->controller.insert(std::make_pair(path, caller));
}

void BasicRequestHandler::setLogger(ILogger *logger) {
    this->logger = logger;
}
