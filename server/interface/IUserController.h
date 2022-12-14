//
// Created by BEMELON on 22. 12. 14.
//

#ifndef MUD_SERVER_IUSERCONTROLLER_H
#define MUD_SERVER_IUSERCONTROLLER_H

#include "IController.h"

class IUserController: public IController {
protected:
    IUserService* userService;
public:
    void setLogger(ILogger *iLogger) override = 0;
    virtual void setUserService(IUserService* iUserService) = 0;

    IResponseDTO * get(IRequestDTO *body, IResponseDTO *resp) override = 0;
    void addRoute(IRequestHandler *handler) override = 0;
};
#endif //MUD_SERVER_IUSERCONTROLLER_H
