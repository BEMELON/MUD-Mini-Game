//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_JSONBUILDER_H
#define MUD_SERVER_JSONBUILDER_H
#include <iostream>
#include "rapidjson/document.h"

using namespace std;
class JsonBuilder {
private:
    rapidjson::Document d;

public:
    JsonBuilder();

    JsonBuilder &add(const string& key, const string& value);
    JsonBuilder &add(const string& key, int value);

    string build();
};


#endif //MUD_SERVER_JSONBUILDER_H
