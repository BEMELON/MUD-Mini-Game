//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_BASICREQUESTHANDLER_H
#define MUD_SERVER_BASICREQUESTHANDLER_H
#include "../interface/IRequestHandler.h"
#define MAX_BUFFER 1024
#define MSG_BUFFER 1536
class BasicRequestHandler: public IRequestHandler {
private:

public:
    void listen(int port) override;
    void addRoute(std::string path, IResponseDTO* (IController::*fn_router)(IRequestDTO*, IResponseDTO*) , IController *caller) override;
};

#endif //MUD_SERVER_BASICREQUESTHANDLER_H
