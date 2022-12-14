//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_IUserRepository_H
#define MUD_SERVER_IUserRepository_H

#include <string>
#include <hiredis/hiredis.h>
#include "../header/User.h"
#include "IDataRepository.h"

#define interface class

interface IUserRepository {
protected:
    IDataRepository *dataRepository;
    ILogger *logger;
public:
    virtual void setLogger(ILogger* iLogger) = 0;
    virtual void setDataRepository(IDataRepository* iDataRepository) = 0;
    virtual User* createUser(User* user) = 0;
    virtual User* updateUser(std::string userId, User* updatedUser) = 0;
    virtual User* delUser(User *user) = 0;

    virtual User* findById(std::string userId) = 0;
    virtual std::list<User *> findAll() = 0;
};

#endif //MUD_SERVER_IUserRepository_H
