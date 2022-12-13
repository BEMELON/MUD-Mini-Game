//
// Created by BEMELON on 22. 12. 11.
//

#ifndef MUD_SERVER_USERCONTROLLER_H
#define MUD_SERVER_USERCONTROLLER_H


#include "../interface/IController.h"

class UserController : public IController {
    void addRoute(IRequestHandler* handler) override;
    IResponseDTO * get(IRequestDTO* body, IResponseDTO* resp) override;
    void setLogger(ILogger *iLogger) override;

    bool login(IRequestDTO* &body, IResponseDTO* &resp);

    bool getAllUser(IRequestDTO* &body, IResponseDTO* &resp);
};


#endif //MUD_SERVER_USERCONTROLLER_H
