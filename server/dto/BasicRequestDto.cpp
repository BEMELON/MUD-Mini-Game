//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/BasicRequestDto.h"

bool BasicRequestDto::has(const string &key) {
    return jsonParser.has(key);
}

void BasicRequestDto::setBody(const string& body) {
    jsonParser.parse(body);
}

string BasicRequestDto::getString(const string& key) {
    return jsonParser.getString(key);
}

int BasicRequestDto::getInt(const string& key) {
    return jsonParser.getInt(key);
}
