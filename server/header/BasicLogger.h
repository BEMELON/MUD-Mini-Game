//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_BASICLOGGER_H
#define MUD_SERVER_BASICLOGGER_H


#include "../interface/ILogger.h"

class BasicLogger: public ILogger {

    void logHeader() override;
    void logInfoMsg(std::string msg) override;
    void logSysErrorMsg(const char *msg) override;
    void logErrorMsg(const char *msg) override;
};


#endif //MUD_SERVER_BASICLOGGER_H
