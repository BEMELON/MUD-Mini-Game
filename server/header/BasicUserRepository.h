//IDataRepository* redisRepository, ILogger *iLogger
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_BASICUSERREPOSITORY_H
#define MUD_SERVER_BASICUSERREPOSITORY_H


#include "../interface/IUserRepository.h"
#include "../interface/IDataRepository.h"

class BasicUserRepository: public IUserRepository {
public:
    BasicUserRepository();
    User* createUser(User *user) override;
    User* delUser(User *user) override;
    list<User *> findAll() override;
    User* findById(std::string userId) override;
    User* updateUser(std::string userId, User *updatedUser) override;
    void setLogger(ILogger *iLogger) override;
    void setDataRepository(IDataRepository *iDataRepository) override;
};


#endif //MUD_SERVER_BASICUSERREPOSITORY_H
