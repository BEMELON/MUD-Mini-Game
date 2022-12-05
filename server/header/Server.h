//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_MINI_GAME_SERVER_H
#define MUD_MINI_GAME_SERVER_H


#include <netinet/in.h>
#include "../interface/Logger.h"

class Server {
public:
    const char *const BROADCAST_ADDR = "0.0.0.0";
    int port;
    Logger *logger;

    Server(int port);
    Server(int port, Logger *logger);

    void listen();

private:
    void start();
    struct sockaddr_in *initSockAddr() const;
};


#endif //MUD_MINI_GAME_SERVER_H
