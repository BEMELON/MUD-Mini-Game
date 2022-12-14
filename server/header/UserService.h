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
};


#endif //MUD_SERVER_USERSERVICE_H
