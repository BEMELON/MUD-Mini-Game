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

    void initRequestHandler();
    void initControllers(IController *controllers[]);
public:
    int port;

    Server(int port, ILogger *logger, IRequestHandler *handler, IController *controllers[]);

    void listen();
};


#endif //MUD_MINI_GAME_SERVER_H
