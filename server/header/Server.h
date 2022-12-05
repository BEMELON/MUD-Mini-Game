//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_MINI_GAME_SERVER_H
#define MUD_MINI_GAME_SERVER_H


#include "../interface/Logger.h"

class Server {
public:

    int port;
    Logger *logger;

    Server(int port);
    Server(int port, Logger *logger);

    void listen();

private:
    void start();
};


#endif //MUD_MINI_GAME_SERVER_H
