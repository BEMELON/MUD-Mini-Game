//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_IDATAREPOSITORY_H
#define MUD_SERVER_IDATAREPOSITORY_H

#include "ILogger.h"

#define interface class

interface IDataRepository {
protected:
    ILogger *logger;
public:
    virtual bool connect(const char* addr, int port) = 0;
    virtual void setLogger(ILogger *logger) = 0;
    virtual 
};


#endif //MUD_SERVER_IDATAREPOSITORY_H
