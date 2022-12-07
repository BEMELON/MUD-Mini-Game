//
// Created by BEMELON on 22. 12. 5.
//

#include <fstream>
#include <sstream>
#include "header/Server.h"
#include "header/JsonParser.h"


Server::Server(ILogger *logger, IRequestHandler *handler, IController* controllers[], IRequestDTO* requestDto, IResponseDTO* responseDto, IRepository *repository) {
    logger->logHeader();
    this->logger = logger;
    this->requestHandler = handler;
    this->initConfig();
    this->initRepository(repository);
    this->initRequestHandler(requestDto, responseDto);
    this->initControllers(controllers);
}

void Server::listen() {
    this->requestHandler->listen(this->server_port);
}

void Server::initRequestHandler(IRequestDTO* requestDto, IResponseDTO* responseDto) {
    this->requestHandler->setLogger(this->logger);
    this->requestHandler->setRequestDto(requestDto);
    this->requestHandler->setResponseDTO(responseDto);
}

void Server::initControllers(IController* controllers[]) {
    for(int i = 0; i < sizeof(controllers) / sizeof(IController *); i++) {
        IController *controller = controllers[i];
        controller->addRoute(this->requestHandler);
    }
}

void Server::initConfig() {
    JsonParser configParser = JsonParser();

    std::stringstream configBuffer;
    ifstream ifs;
    ifs.open("../server/config.json");
    configBuffer << ifs.rdbuf();

    configParser.parse(configBuffer.str());
    if (configParser.has("redis-server"))
        this->redis_addr = configParser.getString("redis-server");
    if (configParser.has("redis-port"))
        this->redis_port = configParser.getInt("redis-port");
    if (configParser.has("server-port"))
        this->server_port = configParser.getInt("server-port");
}

void Server::initRepository(IRepository *repository) {
    bool connected;

    repository->setLogger(this->logger);
    connected = repository->connect(this->redis_addr.c_str(), this->redis_port);
}