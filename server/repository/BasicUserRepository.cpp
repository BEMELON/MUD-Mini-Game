//
// Created by BEMELON on 22. 12. 8.
//

#include "../header/BasicUserRepository.h"
#include <algorithm>
#include <random>

BasicUserRepository::BasicUserRepository() {
}


User* BasicUserRepository::createUser(User *user) {
    // 시드값을 얻기 위한 random_device 생성.
    std::random_device rd;

    // random_device 를 통해 난수 생성 엔진을 초기화 한다.
    std::mt19937 gen(rd());

    // 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
    std::uniform_int_distribution<int> dis(1, 30);

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
    // TODO: WTF? bug
    string prefix_x = "SET USER:" + user->getId() + ":x %s";
    redisCommand(this->dataRepository->redis, prefix_x.c_str(), to_string(user->getPos().getX()).c_str());

    string prefix_y = "SET USER:" + user->getId() + ":y %s";
    redisCommand(this->dataRepository->redis, prefix_y.c_str(), to_string(user->getPos().getY()).c_str());


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
        redisCommand(this->dataRepository->redis,"DEL USER:%s:x", userId);
        redisCommand(this->dataRepository->redis,"DEL USER:%s:y", userId);
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
        user->setHpPotion(1);
    else {
        potionCount = std::stoi(reply->str);
        user->setHpPotion(potionCount);
    }

    // set str-potion
    reply = static_cast<redisReply *>(redisCommand(this->dataRepository->redis,
                                                   "GET USER:%s:potion:str", userId.c_str()));
    if (reply->str == nullptr)
        user->setStrPotion(1);
    else {
        potionCount = std::stoi(reply->str);
        user->setStrPotion(potionCount);
    }

    // 시드값을 얻기 위한 random_device 생성.
    std::random_device rd;

    // random_device 를 통해 난수 생성 엔진을 초기화 한다.
    std::mt19937 gen(rd());

    // 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
    std::uniform_int_distribution<int> dis(1, 30);


    // set user-x
    int x, y;
    reply = static_cast<redisReply *>(redisCommand(this->dataRepository->redis,
                                                   "GET USER:%s:x", userId.c_str()));
    if (reply->str == nullptr) {
      x = dis(gen);
    } else {
        x = std::stoi(reply->str);
    }

    // set user-y
    reply = static_cast<redisReply *>(redisCommand(this->dataRepository->redis,
                                                   "GET USER:%s:y", userId.c_str()));
    if (reply->str == nullptr) {
        y = dis(gen);
    } else {
        y = std::stoi(reply->str);
    }
    user->setPos(x, y);

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
    const list<HpPotion *> &hpPotions = updatedUser->getHpPotions();

    redisCommand(this->dataRepository->redis,
                 "SET USER:%s:potion:hp %s", user->getId().c_str(), std::to_string(hpPotions.size()).c_str());
    redisCommand(this->dataRepository->redis,
                 "SET USER:%s:potion:str %s", user->getId().c_str(), std::to_string(hpPotions.size()).c_str());

    int x = updatedUser->getPos().getX();
    int y = updatedUser->getPos().getY();
    redisCommand(this->dataRepository->redis,
                 "SET USER:%s:x %s", user->getId().c_str(), std::to_string(x).c_str());
    redisCommand(this->dataRepository->redis,
                 "SET USER:%s:y %s", user->getId().c_str(), std::to_string(y).c_str());

    this->logger->logInfoMsg("[UpdateUser] User " + user->getId() + " has been updated! ");

    return updatedUser;
}

void BasicUserRepository::setLogger(ILogger *iLogger) {
    this->logger = iLogger;
}

void BasicUserRepository::setDataRepository(IDataRepository *iDataRepository) {
    this->dataRepository = iDataRepository;
}


