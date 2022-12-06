//
// Created by BEMELON on 22. 12. 5.
//

#include <fstream>
#include <sstream>
#include "header/Server.h"
#include "header/BasicLogger.h"
#include "header/rapidjson/writer.h"
#include "header/BasicRequestHandler.h"
#include "header/JsonParser.h"


Server::Server(ILogger *logger, IRequestHandler *handler, IController* controllers[], IRequestDTO* requestDto, IResponseDTO* responseDto) {
    this->logger = logger;
    this->requestHandler = handler;
    this->initConfig();
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
    // TODO: fix-me
    ifs.open("/home/hgdkim2/Desktop/MUD-Mini-Game/server/config.json");
    cout << ifs.fail() << endl;
    configBuffer << ifs.rdbuf();

    cout << configBuffer.str() << endl;
    configParser.parse(configBuffer.str());
    if (configParser.has("redis-server"))
        this->redis_addr = configParser.getString("redis-server");
    if (configParser.has("redis-port"))
        this->redis_port = configParser.getInt("redis-port");
    if (configParser.has("server-port"))
        this->server_port = configParser.getInt("server-port");
}