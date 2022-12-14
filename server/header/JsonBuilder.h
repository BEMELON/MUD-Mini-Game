//
// Created by BEMELON on 22. 12. 6.
//

#ifndef MUD_SERVER_JSONBUILDER_H
#define MUD_SERVER_JSONBUILDER_H
#include <iostream>
#include "rapidjson/document.h"
#include "User.h"

using namespace std;
class JsonBuilder {
private:
    rapidjson::Document d;
    rapidjson::Value buildUser(User &user);
public:
    JsonBuilder();

    JsonBuilder &add(const string& key, const string& value);
    JsonBuilder &add(const string& key, int value);
    JsonBuilder &setUser(User &user);
    JsonBuilder &addUsers(list<User> &users);
    string build();

    void clean();
};


#endif //MUD_SERVER_JSONBUILDER_H
