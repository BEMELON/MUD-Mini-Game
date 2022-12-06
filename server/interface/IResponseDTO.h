//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_IRESPONSEDTO_H
#define MUD_SERVER_IRESPONSEDTO_H
#define interface class
#include <iostream>

interface IResponseDTO {
public:
    virtual std::string getJsonMsg() = 0;
};

#endif //MUD_SERVER_IRESPONSEDTO_H
