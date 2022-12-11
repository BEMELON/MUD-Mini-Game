//
// Created by BEMELON on 22. 12. 8.
//

#include "../header/BasicUserRepository.h"
#include "../header/HpPotion.h"
#include "../header/StrPotion.h"
#include <iostream>
#include <algorithm>

BasicUserRepository::BasicUserRepository(IDataRepository* dataRepository, ILogger *logger) {
    this->dataRepository = dataRepository;
    this->logger = logger;
}


User* BasicUserRepository::createUser(User *user) {
    redisReply* reply;
    const char* userId = user->getId().c_str();

    // TODO conn for 5 minutes
    redisCommand(this->dataRepository->redis,"SET USER:%s 1", userId);

    // SET HP 30
    redisCommand(this->dataRepository->redis,"SET USER:%s:hp 30", userId);

    // SET STR 3
    redisCommand(this->dataRepository->redis,"SET USER:%s:str 3", userId);

    // SET HpPotion 1
    redisCommand(this->dataRepository->redis,"SET USER:%s:potion:hp 1", userId);

    // SET StrPotion 1
    redisCommand(this->dataRepository->redis,"SET USER:%s:potion:str 1", userId);

    // SET random Coordinate
    // TODO: Add Coordinate
//    redisCommand(this->dataRepository->redis,"SET USER:%s:potion:hp 1", userId);


    logger->logInfoMsg("[CREATE_USER] User " + user->getId() + " has been created!");
    return user;
}

User *BasicUserRepository::delUser(User *user) {
    redisReply* reply;

    reply = static_cast<redisReply *>(redisCommand(this->dataRepository->redis,
                                                   "GET USER:%s",
                                                   user->getId().c_str()));
    if (reply == nullptr)
        logger->logErrorMsg("SET USER failed");
    else if (reply->str == nullptr) {
        logger->logInfoMsg("[delUser] User " + user->getId() + " does not exist.");
    } else {
        const char* userId = user->getId().c_str();
        // TODO: Delete Coordinate
        redisCommand(this->dataRepository->redis,"DEL USER:%s", userId);
        redisCommand(this->dataRepository->redis,"DEL USER:%s:hp", userId);
        redisCommand(this->dataRepository->redis,"DEL USER:%s:str", userId);
        redisCommand(this->dataRepository->redis,"DEL USER:%s:potion:hp", userId);
        redisCommand(this->dataRepository->redis,"DEL USER:%s:potion:str", userId);
        logger->logInfoMsg("[DELETE_USER] User " + user->getId() + " deleted!");
    }

    return user;
}

std::list<User *> BasicUserRepository::findAll() {
    redisReply* reply;
    std::string userId;
    list<User *> users;

    reply = static_cast<redisReply *>(redisCommand(this->dataRepository->redis,"KEYS USER:*"));
    for(int i = 0; i < reply->elements; i++) {
        userId = reply->element[i]->str;
        if (std::count(userId.begin(), userId.end(), ':') == 1) { // USER:TEST1
            users.push_back(findById(userId.substr(userId.find(':') + 1))); // TEST1
        }
    }

    return users;
}

User *BasicUserRepository::findById(std::string userId) {
    redisReply* reply;
    int potionCount = 0;

    reply = static_cast<redisReply *>(redisCommand(this->dataRepository->redis,
                                                   "GET USER:%s", userId.c_str()));

    if (reply && reply->str == nullptr) {
        this->logger->logInfoMsg("[findUser] No user found by id : " + userId);
        return nullptr;
    }

    User* user = new User(userId);

    // set HP
    reply = static_cast<redisReply *>(redisCommand(this->dataRepository->redis,
                                                   "GET USER:%s:hp", userId.c_str()));
    if (reply->str == nullptr)
        user->setHp(30);
    else
        user->setHp(std::stoi(reply->str));

    // set str
    reply = static_cast<redisReply *>(redisCommand(this->dataRepository->redis,
                                                   "GET USER:%s:str", userId.c_str()));
    if (reply->str == nullptr)
        user->setStr(3);
    else
        user->setStr(std::stoi(reply->str));

    // set hp-potion
    reply = static_cast<redisReply *>(redisCommand(this->dataRepository->redis,
                                                   "GET USER:%s:potion:hp", userId.c_str()));
    if (reply->str == nullptr)
        user->addPotion(new HpPotion());
    else {
        potionCount = std::stoi(reply->str);
        for(int i = 0; i < potionCount; i++)
            user->addPotion(new StrPotion());
    }

    // set str-potion
    reply = static_cast<redisReply *>(redisCommand(this->dataRepository->redis,
                                                   "GET USER:%s:potion:str", userId.c_str()));
    if (reply->str == nullptr)
        user->addPotion(new StrPotion());
    else {
        potionCount = std::stoi(reply->str);
        for(int i = 0; i < potionCount; i++)
            user->addPotion(new StrPotion());
    }

    return user;
}


User *BasicUserRepository::updateUser(std::string userId, User *updatedUser) {
    redisReply* reply;
    User* user = findById(userId);

    if (user == nullptr)
        return nullptr;


    // update HP
    if (user->getHp() != updatedUser->getHp())
        redisCommand(this->dataRepository->redis,
                    "SET USER:%s:hp %s", user->getId().c_str(), std::to_string(updatedUser->getHp()).c_str());

    // TODO : update Coordinate

    // update STR
    if (user->getStr() != updatedUser->getStr())
        redisCommand(this->dataRepository->redis,
                     "SET USER:%s:str %s", user->getId().c_str(), std::to_string(updatedUser->getStr()).c_str());


    // update HP potion
    const list<IPotion *> &potions = updatedUser->getPotions();
    int cntHpPotion = 0;
    int cntStrPotion = 0;
    for(auto potion: potions) {
        HpPotion* hpPotion = dynamic_cast<HpPotion *>(potion);

        if (hpPotion == nullptr) {
            cntStrPotion++;
        } else {
            cntHpPotion++;
        }
    }

    redisCommand(this->dataRepository->redis,
                 "SET USER:%s:potion:hp %s", user->getId().c_str(), std::to_string(cntHpPotion).c_str());
    redisCommand(this->dataRepository->redis,
                 "SET USER:%s:potion:str %s", user->getId().c_str(), std::to_string(cntHpPotion).c_str());

    this->logger->logInfoMsg("[UpdateUser] User " + user->getId() + " has been updated! ");

    return updatedUser;
}

