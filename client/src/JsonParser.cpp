//
// Created by BEMELON on 22. 12. 5.
//

#include "../header/JsonParser.h"


JsonParser::JsonParser() = default;

using namespace rapidjson;
void JsonParser::parse(const string &raw) {
    this->d.Parse(raw.c_str());

    this->parseError |= d.HasParseError();
}

bool JsonParser::has(const string &key) {
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

User *JsonParser::getUser(const string &key) {
    const Value& user_json = d["user"].GetObject();
    User* user = new User(user_json["id"].GetString());
    user->setStr(std::stoi(user_json["str"].GetString()));
    user->setHp(std::stoi(user_json["hp"].GetString()));
    user->setStrPotion(std::stoi(user_json["str-potion"].GetString()));
    user->setHpPotion(std::stoi(user_json["hp-potion"].GetString()));
    int x = std::stoi(user_json["x"].GetString());
    int y = std::stoi(user_json["y"].GetString());
    user->setPos(x, y);

    list<string> messages;
    for(const auto& msg: user_json["messages"].GetArray()) {
        messages.emplace_back(msg.GetString());
    }
    user->setMessages(messages);

    return user;
}
