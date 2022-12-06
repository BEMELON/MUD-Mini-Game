//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/BasicController.h"
#include <iostream>

void BasicController::addRoute(IRequestHandler *handler) {
    handler->addRoute("/", &IController::get, this);
}

rapidjson::Document* BasicController::get(rapidjson::Document *body) {
    std::cout << "Hello BasicController!" << std::endl;

    auto *document = new rapidjson::Document();

    return document;
}