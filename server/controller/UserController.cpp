//
// Created by BEMELON on 22. 12. 11.
//

#include "../header/UserController.h"

void UserController::addRoute(IRequestHandler *handler) {
    handler->addRoute("/user", &IController::get, this);
}

bool UserController::login(IRequestDTO* &body, IResponseDTO* &resp) {
    cout << "Hello User Login" << endl;
    return true;
}

bool UserController::getAllUser(IRequestDTO* &body, IResponseDTO* &resp) {
    cout << "Hello getAllUser" << endl;
    return true;
}

IResponseDTO *UserController::get(IRequestDTO *body, IResponseDTO *resp) {
    std::string path = body->getString("Request URL");
    bool status = true;
    if (std::equal(path.begin(), path.end(), "/user/login")) {
        status = login(body, resp);
    } else if (std::equal(path.begin(), path.end(), "/user")) {
        status = getAllUser(body, resp);
    } else {
        this->logger->logInfoMsg("Not handled by UserController ")
    }

    if (status)
        return resp->setStatus("success");
    return resp->setStatus("fail");
}

void UserController::setLogger(ILogger *iLogger) {
    this->logger = iLogger;
}

