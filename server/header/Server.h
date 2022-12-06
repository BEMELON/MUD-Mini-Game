//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_MINI_GAME_SERVER_H
#define MUD_MINI_GAME_SERVER_H


#include <netinet/in.h>
#include "../interface/ILogger.h"
#include "../interface/IRequestHandler.h"
#include "BasicRequestHandler.h"

class Server {
private:
    ILogger *logger;
    IRequestHandler *requestHandler;
    int server_port;
    std::string redis_addr;
    int redis_port;

    void initRequestHandler(IRequestDTO* requestDto, IResponseDTO* responseDto);
    void initControllers(IController *controllers[]);
    void initConfig();
public:
    Server(ILogger *logger, IRequestHandler *handler, IController *controllers[], IRequestDTO* requestDto, IResponseDTO* responseDto);

    void listen();
};


#endif //MUD_MINI_GAME_SERVER_H
