//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_IUserRepository_H
#define MUD_SERVER_IUserRepository_H

#include <string>
#include "../header/User.h"

#define interface class

interface IUserRepository {
protected:
    virtual User* CMD(std::string cmd) = 0;
public:
    virtual User* create(std::string userId) = 0;
    virtual User* login(std::string userId) = 0;
    virtual User* logout(std::string userId) = 0;
    virtual User* move(User *user, Coordinate vector) = 0;
    virtual User* attack(User *user) = 0;
    virtual User* chat(User *src, User *target, std::string content) = 0;
    virtual User* addPotion(User *user, IPotion potion) = 0;
    virtual User* usePotion(User *user, )

};

#endif //MUD_SERVER_IUserRepository_H
