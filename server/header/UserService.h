//
// Created by BEMELON on 22. 12. 14.
//

#ifndef MUD_SERVER_USERSERVICE_H
#define MUD_SERVER_USERSERVICE_H

#include "../interface/IUserService.h"
#include "User.h"

class UserService: public IUserService {

public:
    UserService();
    User* login(string userId) override;
    void setLogger(ILogger *iLogger) override;
    void setUserRepository(IUserRepository *iUserRepository) override;
    bool updateUser(User *user) override;
    bool moveUser(User *pUser, int x, int y) override;
    User * findUserById(string userId) override;
    User * findUserById(string userId, bool message) override;
    bool sendMsg(User *from, User *to, string msg) override;
    bool attack(User* user) override;
    bool resetSession(User *user) override;
    bool usePotion(User* user, string type) override;
    list<User *> findAllUser() override;
};


#endif //MUD_SERVER_USERSERVICE_H
