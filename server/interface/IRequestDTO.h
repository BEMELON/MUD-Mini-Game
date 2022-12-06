//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_IREQUESTDTO_H
#define MUD_SERVER_IREQUESTDTO_H
#define interface class
#include "../header/rapidjson/document.h"

interface IRequestDTO {

protected:
    rapidjson::Document* document;

public:
    void setDocument(rapidjson::Document* document) {
        this->document = document;
    }
};

#endif //MUD_SERVER_IREQUESTDTO_H
