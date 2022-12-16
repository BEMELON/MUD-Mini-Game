//
// Created by BEMELON on 22. 12. 11.
//

#ifndef MUD_SERVER_IUSERSERVICE_H
#define MUD_SERVER_IUSERSERVICE_H
#define interface class
#include "../header/User.h"
#include "IUserRepository.h"

interface IUserService {
protected:
    IUserRepository* userRepository;
    ILogger* logger;
public:
    virtual void setLogger(ILogger *iLogger) = 0;
    virtual void setUserRepository(IUserRepository* iUserRepository) = 0;
    virtual User* login(string userId) = 0;
    virtual bool updateUser(User *user) = 0;
    virtual bool moveUser(User *pUser, string basicString) = 0;
    virtual User* findUserById(string userId) = 0;
    virtual bool sendMsg(User* from, User* to, string msg) = 0;
    virtual bool attack(User* user) = 0;
    virtual bool resetSession(User* user) = 0;
};
#endif //MUD_SERVER_IUSERSERVICE_H
