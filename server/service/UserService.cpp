//
// Created by BEMELON on 22. 12. 14.
//

#include "../header/UserService.h"

UserService::UserService() {
}

void UserService::setLogger(ILogger *iLogger) {
    this->logger = iLogger;
}

void UserService::setUserRepository(IUserRepository *iUserRepository) {
    this->userRepository = iUserRepository;
}

User* UserService::login(string userId) {
    User *user = this->userRepository->findById(userId);
    if (user == nullptr)
        user = this->userRepository->createUser(new User(userId));
    return (user);
}


bool UserService::updateUser(User *user) {
    User* origin_user = this->userRepository->findById(user->getId());
    if (origin_user == nullptr)
        return false;

    this->userRepository->updateUser(origin_user->getId(), user);
    return true;
}

bool UserService::moveUser(User* pUser, string direction) {
    int vec_x = 0;
    int vec_y = 0;
    if (direction == "UP") {
        vec_y = 1;
    } else if (direction == "DOWN") {
        vec_y = -1;
    } else if (direction == "RIGHT") {
        vec_x = 1;
    } else if (direction == "LEFT") {
        vec_x = -1;
    } else {
        return false;
    }

    Coordinate org_pos = pUser->getPos();
    pUser->setPos(org_pos.getX() + vec_x, org_pos.getY() + vec_y);

    this->userRepository->updateUser(pUser->getId(), pUser);
}

User *UserService::findUserById(string userId) {
    return this->userRepository->findById(userId);
}

bool UserService::sendMsg(User* from, User* to, string msg) {
    // TODO : Session update User* from
    to->addMessage(msg);
    User* to_updated = this->userRepository->updateUser(to->getId(), to);

    if (to_updated == nullptr)
        return false;

    return true;
}

bool UserService::attack(User* user) {
    return true;
}
