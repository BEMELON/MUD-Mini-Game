//    this->dataRepository->connect("127.0.0.1", 6379);

// Created by BEMELON on 22. 12. 5.
//
#ifndef MUD_SERVER_IDATAREPOSITORY_H
#define MUD_SERVER_IDATAREPOSITORY_H

#include "ILogger.h"
#include "hiredis/hiredis.h"
#define interface class

interface IDataRepository {
protected:
    ILogger *logger;
public:
    // FIX-ME
    redisContext* redis;

    virtual bool connect(const char* addr, int port) = 0;
    virtual void setLogger(ILogger *logger) = 0;
};


#endif //MUD_SERVER_IDATAREPOSITORY_H
