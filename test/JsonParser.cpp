//
// Created by BEMELON on 22. 12. 5.
//



#include "../server/header/JsonParser.h"

JsonParser::JsonParser() = default;

void JsonParser::parse(const string& raw) {
    this->d.Parse(raw.c_str());

    this->parseError |= d.HasParseError();
}

bool JsonParser::has(const string& key) {
    return d.HasMember(key.c_str());
}

bool JsonParser::hasError() const {
    return this->parseError;
}

rapidjson::Document *JsonParser::getDocument() {
    return &this->d;
}

string JsonParser::getString(const string& key) {
    return d[key.c_str()].GetString();
}

int JsonParser::getInt(const string& key) {
    return d[key.c_str()].GetInt();
}