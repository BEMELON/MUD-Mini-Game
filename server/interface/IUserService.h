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
};
#endif //MUD_SERVER_IUSERSERVICE_H
