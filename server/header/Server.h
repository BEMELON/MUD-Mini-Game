//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_MINI_GAME_SERVER_H
#define MUD_MINI_GAME_SERVER_H


#include <netinet/in.h>
#include "../interface/ILogger.h"
#include "../interface/IRequestHandler.h"
#include "BasicRequestHandler.h"
#include "../interface/IDataRepository.h"
#include "../interface/IUserController.h"

class Server {
private:
    ILogger*            logger;
    IRequestHandler*    requestHandler;
    IDataRepository*    dataRepository;
    IRequestDTO*        requestDto;
    IResponseDTO*       responseDto;
    IUserController*    userController;
    IUserService*       userService;
    IUserRepository*    userRepository;
    int                 server_port;
    int                 redis_port;
    std::string         redis_addr;
    IController*        healthController;

    void initDataRepository();
    void initConfig();
    void initLogger(ILogger *iLogger);
public:
    Server(ILogger* iLogger);
    void setEventHandler(IRequestHandler *handler, IRequestDTO *requestDto, IResponseDTO *responseDto);
    void setDataRepository(IDataRepository* dataRepository);
    void setUserStack(IUserController* iUserController, IUserService* iUserService, IUserRepository* iUserRepository);
    void setHealthController(IController* iController);
    void listen();
};


#endif //MUD_MINI_GAME_SERVER_H
