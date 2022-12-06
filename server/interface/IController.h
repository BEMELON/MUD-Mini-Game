//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_ICONTROLLER_H
#define MUD_SERVER_ICONTROLLER_H
#include "IRequestHandler.h"
#include "IRequestDTO.h"
#include "IResponseDTO.h"
#define interface class

class IRequestHandler;

interface IController {
public:
    virtual void addRoute(IRequestHandler *handler) = 0;
    virtual IResponseDTO*  get(IRequestDTO* body, IResponseDTO* resp) = 0;
};


#endif //MUD_SERVER_ICONTROLLER_H
