//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_RESPONSEDTO_H
#define MUD_SERVER_RESPONSEDTO_H
#include "../interface/IResponseDTO.h"
#include "rapidjson/document.h"
#include <iostream>

class ResponseDto: public IResponseDTO {
protected:
    std::string msg;
    std::string json_msg;
public:
    ResponseDto();
    ResponseDto(const char *msg);

    std::string getJsonMsg() override;
    IResponseDTO* setStatus(const char *status) override;
    void addUsers(list<User *> users) override;
    void setUser(User user) override;
    void clean() override;
};


#endif //MUD_SERVER_RESPONSEDTO_H
