//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/BasicController.h"
#include "../header/ResponseDto.h"
#include <iostream>

void BasicController::addRoute(IRequestHandler *handler) {
    handler->addRoute("/", &IController::get, this);
}

IResponseDTO* BasicController::get(IRequestDTO* body, IResponseDTO* resp) {
    std::cout << "Hello BasicController!" << std::endl;

    return resp->setStatus("success");
}

void BasicController::setLogger(ILogger *iLogger) {
    this->logger = iLogger;
}

void BasicController::setUserService(IUserService *iUserService) {
    this->userService = iUserService;
}
