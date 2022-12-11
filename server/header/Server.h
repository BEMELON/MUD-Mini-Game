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

class Server {
private:
    ILogger*            logger;
    IRequestHandler*    requestHandler;
    IDataRepository*    dataRepository;
    int                 server_port;
    int                 redis_port;
    std::string         redis_addr;

    void initRequestHandler(IRequestDTO* requestDto, IResponseDTO* responseDto);
    void initControllers(IController* controllers[]);
    void initDataRepository(IDataRepository* repository);
    void initConfig();
public:
    Server(ILogger* logger, IRequestHandler* handler, IController* controllers[],
           IRequestDTO* requestDto, IResponseDTO* responseDto, IDataRepository* repository);

    void listen();
};


#endif //MUD_MINI_GAME_SERVER_H
