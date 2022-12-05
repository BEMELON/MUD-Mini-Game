//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_MINI_GAME_LOGGER_H
#define MUD_MINI_GAME_LOGGER_H
#define interface class

interface Logger {
        public:
        virtual void logHeader() = 0;

        virtual void logInfoMsg(std::string msg) = 0;
//    virtual void logWarningMsg(std::string msg) = 0;
        virtual void logSysErrorMsg(const char *msg) = 0;
};


#endif //MUD_MINI_GAME_LOGGER_H
