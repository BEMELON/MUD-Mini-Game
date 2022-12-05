//
// Created by BEMELON on 22. 12. 5.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <csignal>
#include "../header/Server.h"
#include <iostream>
#include "../header/NaiveLogger.h"

Server::Server(int port) {
    this->port = port;
    this->logger = new NaiveLogger();
}

Server::Server(int port, Logger *logger) {
    this->logger = logger;
    this->port = port;
}

void Server::listen() {
    this->logger->logHeader();
    this->logger->logInfoMsg("Server started at port " + std::to_string(this->port));
    this->start();
}

void Server::start() {
    int fd;
    struct sockaddr_in server_addr;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        this->logger->logSysErrorMsg("Sock Error");

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    if ((bind(fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))) < 0)
        this->logger->logSysErrorMsg("Bind Error");

    int active_fd;
    if ((active_fd = ::listen(fd, 30)) < 0)
        this->logger->logSysErrorMsg("Listen Error");

    struct sockaddr_in client_addr;
    socklen_t client_len;

    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    client_len = 0;

    this->logger->logInfoMsg("Waiting for client ...");
    if ((active_fd = accept(fd, (struct sockaddr *)&client_addr, &client_len)) < 0)
        this->logger->logSysErrorMsg("Accept Error");

    char buffer[256];
    while (read(active_fd, buffer, 256) > 0) {
        std::cout << "Client sends " << buffer << std::endl;

        char ack[256] = "accepted";
        if (send(active_fd, ack, 256, 0) < 0)
            this->logger->logSysErrorMsg("Send Error");
    }
}