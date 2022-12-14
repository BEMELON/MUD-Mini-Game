//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_JSONPARSER_H
#define MUD_SERVER_JSONPARSER_H
#include <iostream>
#include "rapidjson/document.h"
#include "User.h"

using namespace std;

class JsonParser {
private:
    rapidjson::Document d;
    bool parseError = false;
public:
    JsonParser();
    void parse(const string& raw);

    bool has(const string& key);

    string getString(const string& key);
    int getInt(const string& key);
    User* getUser(const string& key);
    bool hasError() const;

    rapidjson::Document* getDocument();
};


#endif //MUD_SERVER_JSONPARSER_H
