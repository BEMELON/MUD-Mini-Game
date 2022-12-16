//
// Created by BEMELON on 22. 12. 15.
//

#ifndef MUD_SERVER_EPOLLEVENTHANDLER_H
#define MUD_SERVER_EPOLLEVENTHANDLER_H


#include "../interface/IRequestHandler.h"

class EpollEventHandler: public IRequestHandler {
public:
    void listen(int port) override;
    void addRoute(std::string path, IResponseDTO *(IController::*fn_router)(IRequestDTO *, IResponseDTO *), IController *caller) override;

    string getRoot(const string& basicString);
};


#endif //MUD_SERVER_EPOLLEVENTHANDLER_H
