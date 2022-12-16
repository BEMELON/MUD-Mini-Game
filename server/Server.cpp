//
// Created by BEMELON on 22. 12. 5.
//

#include <fstream>
#include <sstream>
#include "header/Server.h"
#include "header/JsonParser.h"


Server::Server(ILogger *iLogger) {
    this->initLogger(iLogger);
    this->initConfig();
}

void Server::listen() {
    this->requestHandler->listen(this->server_port);
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

    if (this->redis_port == 0 || this->redis_addr.empty() || this->server_port == 0)
        this->logger->logErrorMsg("[Init] fail to init config.json");
    this->logger->logInfoMsg("[Init] config.json initialized");
}

void Server::initDataRepository() {
    this->dataRepository->setLogger(this->logger);
    this->dataRepository->connect(this->redis_addr.c_str(), this->redis_port);
    this->logger->logInfoMsg("[Init] RedisRepository initialized");
}

void Server::setEventHandler(IRequestHandler *handler, IRequestDTO *iRequestDto, IResponseDTO *iResponseDto) {
    this->requestHandler = handler;
    this->requestDto = iRequestDto;
    this->responseDto = iResponseDto;

    this->requestHandler->setRequestDto(this->requestDto);
    this->requestHandler->setResponseDTO(this->responseDto);
    this->requestHandler->setLogger(this->logger);

    this->logger->logInfoMsg("[Init] EventHandler initialized.");
}


void Server::setDataRepository(IDataRepository* dataRepository) {
    this->dataRepository = dataRepository;
    this->initDataRepository();
}

void Server::initLogger(ILogger *iLogger) {
    this->logger = iLogger;
    this->logger->logHeader();
}

void Server::setUserStack(IUserController *iUserController, IUserService *iUserService, IUserRepository *iUserRepository) {
    this->userController = iUserController;
    this->userService = iUserService;
    this->userRepository = iUserRepository;

    if (this->requestHandler == nullptr)
        this->logger->logErrorMsg("[Init] You should call [setEventHandler] first");
    this->userController->setLogger(this->logger);
    this->userController->setUserService(this->userService);
    this->userController->addRoute(this->requestHandler);
    this->logger->logInfoMsg("[Init] UserController initialized.");

    this->userService->setLogger(this->logger);
    this->userService->setUserRepository(userRepository);
    this->logger->logInfoMsg("[Init] UserService initialized.");

    this->userRepository->setLogger(this->logger);
    this->userRepository->setDataRepository(this->dataRepository);

    this->logger->logInfoMsg("[Init] UserRepository initialized.");
}

void Server::setHealthController(IController *iController) {
    this->healthController = iController;
    this->healthController->addRoute(this->requestHandler);
    this->healthController->setLogger(this->logger);
    this->logger->logInfoMsg("[Init] HealthController initialized.");
}
