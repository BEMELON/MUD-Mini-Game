//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/RequestDto.h"

bool RequestDto::has(const string &key) {
    return jsonParser.has(key);
}

void RequestDto::setBody(const string& body) {
    jsonParser.parse(body);
}

string RequestDto::getString(const string& key) {
    return jsonParser.getString(key);
}

int RequestDto::getInt(const string& key) {
    return jsonParser.getInt(key);
}

User *RequestDto::getUser() {
    return jsonParser.getUser("user");
}
