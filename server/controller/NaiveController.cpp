//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/NaiveController.h"
#include <iostream>

void NaiveController::addRoute(IRequestHandler *handler) {
    handler->addRoute("/", &IController::get, this);
}

void NaiveController::get(rapidjson::Document *body) {
    std::cout << "Hello World!" << std::endl;
}