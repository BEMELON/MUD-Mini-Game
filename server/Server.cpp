//
// Created by BEMELON on 22. 12. 5.
//

#include "header/Server.h"
#include "header/BasicLogger.h"
#include "header/rapidjson/writer.h"
#include "header/BasicRequestHandler.h"


Server::Server(int port, ILogger *logger, IRequestHandler *handler, IController *controllers[]) {
    this->logger = logger;
    this->port = port;
    this->requestHandler = handler;
    this->initRequestHandler();
    this->initControllers(controllers);
}

void Server::listen() {
    this->requestHandler->listen(this->port);
}

void Server::initRequestHandler() {
    this->requestHandler->setLogger(this->logger);
}

void Server::initControllers(IController *controllers[]) {
    for(int i = 0; i < sizeof(controllers) / sizeof(IController *); i++) {
        IController *controller = controllers[i];
        controller->addRoute(this->requestHandler);
    }
}