//
// Created by BEMELON on 22. 12. 7.
//

#ifndef MUD_SERVER_REDISREPOSITORY_H
#define MUD_SERVER_REDISREPOSITORY_H


#include "../interface/IDataRepository.h"
#include "hiredis/hiredis.h"

class RedisRepository: public IDataRepository {
private:
    const int MAX_SESSION_SEC = 300;
    redisContext *conn;
public:
    RedisRepository();
    bool connect(const char* addr, int port) override;
    void setLogger(ILogger *logger) override;
};


#endif //MUD_SERVER_REDISREPOSITORY_H
