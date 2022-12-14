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
    this->port = port;

    struct sockaddr_in server_addr, client_addr; // 서버/클라이언트 구조체
    int passive_fd, active_fd; // Passive / Active 소켓
    socklen_t client_len = 0; // Socket len (ignored)
    JsonParser jsonParser = JsonParser();


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

    this->logger->logInfoMsg("[Init] Server started at port " + std::to_string(port));

    while (true) {
        if ((active_fd = accept(passive_fd, (struct sockaddr *)&client_addr, &client_len)) < 0)
            this->logger->logSysErrorMsg("Accept Error");

        if ((pid = fork()) < 0)
            this->logger->logSysErrorMsg("Fork Error");

        if (pid == 0) {
            sprintf(msg, "[EventHandler] new User Connected, new process has been created : %d", getpid());
            this->logger->logInfoMsg(msg);

            memset(buffer, 0, MAX_BUFFER);
            if (recv(active_fd, buffer, MAX_BUFFER, 0) < 0)
                this->logger->logSysErrorMsg("Read failed");

            jsonParser.parse(buffer);

            string url = jsonParser.getString("Request URL"); // /user/create
            string root = getRoot(url);
            auto fn = this->router.find(root)->second;
            IController *controller = this->controller.find(root)->second;

            this->requestDto->setBody(buffer);
            IResponseDTO* res = (controller->*fn)(this->requestDto, this->responseDto);

            if (send(active_fd, res->getJsonMsg().c_str(), res->getJsonMsg().size(), 0) < 0)
                this->logger->logSysErrorMsg("Send Error");
            exit(EXIT_SUCCESS);
        }
    }
}

string BasicRequestHandler::getRoot(string path) {
    int first_slash = path.find('/', 0);
    int second_slash = path.find('/', first_slash + 1);

    if (second_slash == string::npos)
        return path.substr(first_slash);
    else
        return path.substr(first_slash, second_slash - first_slash);
}

void BasicRequestHandler::addRoute(std::string path, IResponseDTO* (IController::*fn_router)(IRequestDTO*, IResponseDTO*), IController *caller) {
    this->router.insert(std::make_pair(path, fn_router));
    this->controller.insert(std::make_pair(path, caller));
}

