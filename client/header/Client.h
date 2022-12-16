//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_CLIENT_H
#define MUD_SERVER_CLIENT_H
#include <string>
#include "../interface/Logger.h"
#include "User.h"
#include "JsonParser.h"

using namespace std;
class Client {
private:
    int port;
    int fd;
    Logger *logger;
    User* user;
    JsonParser jsonParser;
public:
    Client(int port, Logger *logger);
    int connect();
    bool send(std::string msg);
    void start();

    bool login(string userId);

    void updateUserInfo();
    void printUserCoordinate();
    void printUserHp();
    void printUserStr();
    void printUserPotions();
    bool getCmd();

    void move(string cmd);
    void potion(string cmd);
    void attack();
    void status();
    void sendMsg(string cmd);

    void printUser();

    void close();

    void printMessages();

    void getMessage();
};


#endif //MUD_SERVER_CLIENT_H
