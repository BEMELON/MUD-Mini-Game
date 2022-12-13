//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_IREQUESTDTO_H
#define MUD_SERVER_IREQUESTDTO_H
#define interface class
#include "../header/rapidjson/document.h"
#include "../header/JsonParser.h"

interface IRequestDTO {

protected:

public:
    virtual void setBody(const std::string& body)  = 0;
    virtual std::string getString(const std::string& key) = 0;
    virtual int getInt(const std::string& key) = 0;
    virtual bool has(const std::string& key) = 0;
};

#endif //MUD_SERVER_IREQUESTDTO_H
