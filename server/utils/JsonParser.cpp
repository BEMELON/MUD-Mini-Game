//
// Created by BEMELON on 22. 12. 5.
//

#include "../header/JsonParser.h"


JsonParser::JsonParser() {

}

void JsonParser::parse(string raw) {
    this->d.Parse(raw.c_str());

    this->parseError |= d.HasParseError();
}

bool JsonParser::has(string key) {
    return d.HasMember(key.c_str());
}

bool JsonParser::hasError() {
    return this->parseError;
}

string JsonParser::getString(string key) {
    return d[key.c_str()].GetString();
}

int JsonParser::getInt(string key) {
    return d[key.c_str()].GetInt();
}