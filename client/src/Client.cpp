//
// Created by BEMELON on 22. 12. 5.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "../header/Client.h"
#include "../interface/Logger.h"

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

int Client::send(std::string msg) {
    char buffer[256];

    strcpy(buffer, msg.c_str());
    if (::send(this->fd, buffer, 256, 0) < 0)
        this->logger->logSysErrorMsg("Send Error");

    memset(buffer, 0, 256);
    if (recv(this->fd, buffer, 256, 0) < 0)
        this->logger->logSysErrorMsg("Recv Error");
    this->logger->logInfoMsg(buffer);
    return 1;
}