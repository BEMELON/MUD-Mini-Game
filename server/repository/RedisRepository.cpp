//
// Created by BEMELON on 22. 12. 7.
//

#include "../header/RedisRepository.h"

RedisRepository::RedisRepository() {

}

bool RedisRepository::connect(const char *addr, int port) {
    this->conn = redisConnect(addr, port);
    if (this->conn == nullptr|| this->conn->err) {
        this->logger->logSysErrorMsg(this->conn->errstr);
        return false;
    }
    this->logger->logInfoMsg("Redis Connected!");
    return true;
}

void RedisRepository::setLogger(ILogger *logger) {
    this->logger = logger;
}