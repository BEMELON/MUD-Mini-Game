//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_CLIENT_H
#define MUD_SERVER_CLIENT_H
#include <string>
#include "../interface/Logger.h"

class Client {
private:
    int port;
    int fd;
    Logger *logger;
public:
    Client(int port, Logger *logger);

    int connect();
    int send(std::string msg);
};


#endif //MUD_SERVER_CLIENT_H
