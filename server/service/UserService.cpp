//
// Created by BEMELON on 22. 12. 14.
//

#include "../header/UserService.h"

UserService::UserService() {
}


User* UserService::login(string userId) {
    User *user = this->userRepository->findById(userId);

    return (user);
}

void UserService::setLogger(ILogger *iLogger) {
    this->logger = iLogger;
}

void UserService::setUserRepository(IUserRepository *iUserRepository) {
    this->userRepository = iUserRepository;
}
