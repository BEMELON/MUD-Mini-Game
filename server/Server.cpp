//
// Created by BEMELON on 22. 12. 5.
//

#include "header/Server.h"
#include "header/BasicLogger.h"
#include "header/rapidjson/writer.h"
#include "header/BasicRequestHandler.h"


Server::Server(int port, ILogger *logger, IRequestHandler *handler, IController *controllers[], IRequestDTO* requestDto, IResponseDTO* responseDto) {
    this->logger = logger;
    this->port = port;
    this->requestHandler = handler;
    this->initRequestHandler(requestDto, responseDto);
    this->initControllers(controllers);
}

void Server::listen() {
    this->requestHandler->listen(this->port);
}

void Server::initRequestHandler(IRequestDTO* requestDto, IResponseDTO* responseDto) {
    this->requestHandler->setLogger(this->logger);
    this->requestHandler->setRequestDto(requestDto);
    this->requestHandler->setResponseDTO(responseDto);
}

void Server::initControllers(IController *controllers[]) {
    for(int i = 0; i < sizeof(controllers) / sizeof(IController *); i++) {
        IController *controller = controllers[i];
        controller->addRoute(this->requestHandler);
    }
}