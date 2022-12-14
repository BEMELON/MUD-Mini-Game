//
// Created by BEMELON on 22. 12. 11.
//

#include "../header/UserController.h"
#include <regex>

UserController::UserController() {
}

void UserController::addRoute(IRequestHandler *handler) {
    handler->addRoute("/user", &IController::get, this);
    this->logger->logInfoMsg("[Init] UserController Route initialized");
}

bool UserController::login(IRequestDTO* &body, IResponseDTO* &resp) {
    this->logger->logInfoMsg("[DEBUG][UserController][login] called");
    string userId = getUserId(body->getString("Request URL"));
    if (!body->has("userId"))
        return false;

    User* user = this->userService->login(userId);

    if (user == nullptr)
        return false;

    resp->setUser(*user);
    return true;
}

bool UserController::getAllUser(IRequestDTO* &body, IResponseDTO* &resp) {
    this->logger->logInfoMsg("[DEBUG][UserController][getAllUser] called");
    return true;
}

bool UserController::getUserInfo(IRequestDTO* &body, IResponseDTO* &resp) {
    this->logger->logInfoMsg("[DEBUG][UserController][getUserInfo] called");
    return true;
}

bool UserController::moveUser(IRequestDTO* &body, IResponseDTO* &resp) {
    this->logger->logInfoMsg("[DEBUG][UserController][moveUser] called");
    if (!body->has("direction")) return false;

    string userId = getUserId(body->getString("Request URL"));
    User* user = this->userService->login(userId);
    if (user == nullptr) return false;
    string direction = body->getString("direction");
    bool status = this->userService->moveUser(user, direction);

    resp->setUser((*this->userService->login(userId)));
    return status;
}

bool UserController::attack(IRequestDTO *&body, IResponseDTO *&resp) {
    this->logger->logInfoMsg("[DEBUG][UserController][attack] called");
    return true;
}

bool UserController::sendMsg(IRequestDTO *&body, IResponseDTO *&resp) {
    this->logger->logInfoMsg("[DEBUG][UserController][sendMsg] called");
    return true;
}


IResponseDTO *UserController::get(IRequestDTO *body, IResponseDTO *resp) {
    std::string path = body->getString("Request URL");
    bool status = true;
    if (std::regex_match(path, std::regex("/user"))) {
        status = getAllUser(body, resp);
    } else if (std::regex_match(path, std::regex("/user/login"))) {
        status = login(body, resp);
    } else if (std::regex_match(path, std::regex("/user/[^/]+/move"))) {
        status = moveUser(body, resp);
    } else if (std::regex_match(path, std::regex("/user/[^/]+/attack"))) {
        status = attack(body, resp);
    } else if  (std::regex_match(path, std::regex("/user/[^/]+/sendMsg"))) {
        status = sendMsg(body, resp);
    } else if (std::regex_match(path, std::regex("/user/[^/]+"))) {
        status = getUserInfo(body, resp);
    } else {
        this->logger->logInfoMsg("[DEBUG] Not handled by UserController ");
        status = false;
    }
    if (status)
        return resp->setStatus("success");
    return resp->setStatus("fail");
}

void UserController::setLogger(ILogger *iLogger) {
    this->logger = iLogger;
}

void UserController::setUserService(IUserService *iUserService) {
    this->userService = iUserService;
}

string UserController::getUserId(const string &path) {
    int first_slash = path.find('/', 0);
    int second_slash = path.find('/', first_slash + 1);
    int third_slash = path.find('/', second_slash);

    return path.substr(second_slash + 1, third_slash);
}
