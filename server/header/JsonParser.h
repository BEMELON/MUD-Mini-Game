//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_JSONPARSER_H
#define MUD_SERVER_JSONPARSER_H
#include <iostream>
#include "rapidjson/document.h"

using namespace std;

class JsonParser {
private:
    rapidjson::Document d;
    bool parseError = false;
public:
    JsonParser();
    void parse(string raw);

    bool has(string key);

    string getString(string key);
    int getInt(string key);

    bool hasError();
};


#endif //MUD_SERVER_JSONPARSER_H
