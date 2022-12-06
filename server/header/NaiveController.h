//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_NAIVECONTROLLER_H
#define MUD_SERVER_NAIVECONTROLLER_H


#include "../interface/IController.h"

class NaiveController: public IController {
public:
    void addRoute(IRequestHandler *handler) override;
    void get(rapidjson::Document *body) override;
};


#endif //MUD_SERVER_NAIVECONTROLLER_H
