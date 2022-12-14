//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_BASICRESPONSEDTO_H
#define MUD_SERVER_BASICRESPONSEDTO_H
#include "../interface/IResponseDTO.h"
#include "rapidjson/document.h"
#include <iostream>

class BasicResponseDto: public IResponseDTO {
protected:
    std::string msg;
    std::string json_msg;
public:
    BasicResponseDto();
    BasicResponseDto(const char *msg);

    std::string getJsonMsg() override;
    IResponseDTO* setStatus(const char *status) override;
    void addUsers(list<User> users) override;
    void setUser(User user) override;
};


#endif //MUD_SERVER_BASICRESPONSEDTO_H
