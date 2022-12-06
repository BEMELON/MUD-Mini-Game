//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/BasicController.h"
#include <iostream>

void BasicController::addRoute(IRequestHandler *handler) {
    handler->addRoute("/", &IController::get, this);
}

void BasicController::get(rapidjson::Document *body) {
    std::cout << "Hello World!" << std::endl;
}