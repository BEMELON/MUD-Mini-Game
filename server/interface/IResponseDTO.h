//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_IRESPONSEDTO_H
#define MUD_SERVER_IRESPONSEDTO_H
#define interface class
#include <iostream>
#include "../header/User.h"
#include "../header/JsonBuilder.h"

interface IResponseDTO {
protected:
    JsonBuilder jsonBuilder;
public:
    virtual std::string getJsonMsg() = 0;
    virtual IResponseDTO* setStatus(const char *status) = 0;

    virtual void addUsers(list<User> users) = 0;
    virtual void setUser(User user) = 0;
    virtual void clean() = 0;
};

#endif //MUD_SERVER_IRESPONSEDTO_H
