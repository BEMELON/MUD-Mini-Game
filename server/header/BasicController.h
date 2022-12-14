//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_BASICCONTROLLER_H
#define MUD_SERVER_BASICCONTROLLER_H


#include "../interface/IUserController.h"

class BasicController: public IUserController {
public:
    void addRoute(IRequestHandler *handler) override;
    IResponseDTO* get(IRequestDTO* body, IResponseDTO* resp) override;
    void setLogger(ILogger *iLogger) override;
    void setUserService(IUserService *iUserService) override;
};


#endif //MUD_SERVER_BASICCONTROLLER_H
