//
// Created by BEMELON on 22. 12. 7.
//

#include "../header/RedisRepository.h"

RedisRepository::RedisRepository() {

}

bool RedisRepository::connect(const char *addr, int port) {
    this->redis = redisConnect(addr, port);
    if (this->redis == nullptr|| this->redis->err) {
        this->logger->logSysErrorMsg(this->redis->errstr);
        return false;
    }
    this->logger->logInfoMsg("Redis connected with port " + std::to_string(port));
    return true;
}

void RedisRepository::setLogger(ILogger *logger) {
    this->logger = logger;
}
