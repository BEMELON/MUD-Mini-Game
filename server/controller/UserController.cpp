//
// Created by BEMELON on 22. 12. 11.
//

#include "../header/UserController.h"
#include <regex>

void UserController::addRoute(IRequestHandler *handler) {
    handler->addRoute("/user", &IController::get, this);
}

bool UserController::login(IRequestDTO* &body, IResponseDTO* &resp) {
    if (!body->has("userId"))
        return false;

    std::string userId = body->getString("userId");

    return true;
}

bool UserController::getAllUser(IRequestDTO* &body, IResponseDTO* &resp) {
    cout << "Hello getAllUser" << endl;
    return true;
}

bool UserController::getUserInfo(IRequestDTO* &body, IResponseDTO* &resp) {
    cout << "Hello getUserInfo" << endl;
    return true;
}

bool UserController::moveUser(IRequestDTO* &body, IResponseDTO* &resp) {
    cout << "Hello moveUser" << endl;
    return true;
}

bool UserController::attack(IRequestDTO *&body, IResponseDTO *&resp) {
    cout << "Hello attack" << endl;
    return true;
}

bool UserController::sendMsg(IRequestDTO *&body, IResponseDTO *&resp) {
    cout << "Hello sendMsg" << endl;
    return true;
}


IResponseDTO *UserController::get(IRequestDTO *body, IResponseDTO *resp) {
    std::string path = body->getString("Request URL");
    bool status = true;
    if (std::regex_match(path, std::regex("/user"))) {
        status = getAllUser(body, resp);
    } else if (std::regex_match(path, std::regex("/user/login"))) {
        status = login(body, resp);
    } else if (std::regex_match(path, std::regex("/user/\\d*"))) {
        status = getUserInfo(body, resp);
    } else if (std::regex_match(path, std::regex("/user/\\d*/move"))) {
        status = moveUser(body, resp);
    } else if (std::regex_match(path, std::regex("/user/\\d*/attack"))) {
        status = attack(body, resp);
    } else if  (std::regex_match(path, std::regex("/user/\\d*/sendMsg"))) {
        status = sendMsg(body, resp);
    } else {
        this->logger->logInfoMsg("Not handled by UserController ");
    }
    if (status)
        return resp->setStatus("success");
    return resp->setStatus("fail");
}

void UserController::setLogger(ILogger *iLogger) {
    this->logger = iLogger;
}

void UserController::setService(IUserService* iUserService) {
    this->userService = iUserService;
}
