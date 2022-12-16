//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_REQUESTDTO_H
#define MUD_SERVER_REQUESTDTO_H


#include "../interface/IRequestDTO.h"
#include "User.h"

class RequestDto: public IRequestDTO {
private:
    JsonParser jsonParser;
public:
    int getInt(const std::string &key) override;
    bool has(const std::string &key) override;
    std::string getString(const std::string &key) override;
    void setBody(const std::string &body) override;
    User* getUser() override;
};


#endif //MUD_SERVER_REQUESTDTO_H
