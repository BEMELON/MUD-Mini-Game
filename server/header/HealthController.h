//
// Created by BEMELON on 22. 12. 15.
//

#ifndef MUD_SERVER_HEALTHCONTROLLER_H
#define MUD_SERVER_HEALTHCONTROLLER_H


#include "../interface/IController.h"

class HealthController: public IController {
    void setLogger(ILogger *iLogger) override;
    void addRoute(IRequestHandler *handler) override;
    IResponseDTO * get(IRequestDTO *body, IResponseDTO *resp) override;
};


#endif //MUD_SERVER_HEALTHCONTROLLER_H
