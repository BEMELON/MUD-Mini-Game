//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_LOGGER_H
#define MUD_SERVER_LOGGER_H
#define interface class
#include <string>

interface Logger {
public:
    virtual void logHeader() = 0;

    virtual void logInfoMsg(std::string msg) = 0;
//    virtual void logWarningMsg(std::string msg) = 0;
    virtual void logSysErrorMsg(const char *msg) = 0;
};


#endif //MUD_SERVER_LOGGER_H
