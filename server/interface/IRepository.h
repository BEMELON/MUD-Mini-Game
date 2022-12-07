//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_IREPOSITORY_H
#define MUD_SERVER_IREPOSITORY_H

#include "ILogger.h"

#define interface class

interface IRepository {
protected:
    ILogger *logger;
public:
    virtual bool connect(const char* addr, int port) = 0;
    virtual void setLogger(ILogger *logger) = 0;
};


#endif //MUD_SERVER_IREPOSITORY_H
