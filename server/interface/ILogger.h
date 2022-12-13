//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_ILOGGER_H
#define MUD_SERVER_ILOGGER_H
#define interface class
#include <string>

interface ILogger {
public:
    virtual void logHeader() = 0;

    virtual void logInfoMsg(std::string msg) = 0;
    virtual void logErrorMsg(const char *msg) = 0;
    virtual void logWarningMsg(const char *msg) = 0;
    virtual void logSysErrorMsg(const char *msg) = 0;
};


#endif //MUD_SERVER_ILOGGER_H
