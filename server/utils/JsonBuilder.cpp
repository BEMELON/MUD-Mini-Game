//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/JsonBuilder.h"
#include "../header/rapidjson/stringbuffer.h"
#include "../header/rapidjson/prettywriter.h"

using namespace rapidjson;
JsonBuilder::JsonBuilder() {
    d.SetObject();
};

JsonBuilder &JsonBuilder::add(const string& key, int value) {
    Value vName(kStringType);
    vName.SetString(key.c_str(), d.GetAllocator());

    Value vValue(kNumberType);
    vValue.SetInt(value);

    d.AddMember(vName, vValue, d.GetAllocator());

    return *this;
}

JsonBuilder &JsonBuilder::add(const string& key, const string& value) {
    Value vName(kStringType);
    vName.SetString(key.c_str(), d.GetAllocator());

    Value vValue(kStringType);
    vValue.SetString(value.c_str(), d.GetAllocator());

    d.AddMember(vName, vValue, d.GetAllocator());

    return *this;
}


JsonBuilder &JsonBuilder::setUser(User &user) {
    Value user_json = buildUser(user);
    d.AddMember("user", user_json, d.GetAllocator());

    return *this;
}

JsonBuilder &JsonBuilder::addUsers(list<User> &users) {
    Value user_array = Value(Type::kArrayType);
    for(User user: users) {
        user_array.PushBack(buildUser(user), d.GetAllocator());
    }

    d.AddMember("users", user_array, d.GetAllocator());
    return *this;
}


string JsonBuilder::build() {
    StringBuffer strbuf;
    PrettyWriter<StringBuffer> writer(strbuf);
    d.Accept(writer);

    return strbuf.GetString();
}

rapidjson::Value JsonBuilder::buildUser(User &user) {
    Value json(Type::kObjectType);

    Value key_id("id", d.GetAllocator());
    Value value_id(user.getId().c_str(), d.GetAllocator());

    Value key_hp("hp", d.GetAllocator());
    Value value_hp(to_string(user.getHp()).c_str(), d.GetAllocator());

    Value key_str("str", d.GetAllocator());
    Value value_str(to_string(user.getStr()).c_str(), d.GetAllocator());

    Value key_x("x", d.GetAllocator());
    Value value_x(to_string(user.getPos().getX()).c_str(), d.GetAllocator());

    Value key_y("y", d.GetAllocator());
    Value value_y(to_string(user.getPos().getY()).c_str(), d.GetAllocator());

    Value key_hp_potion("hp-potion", d.GetAllocator());
    Value value_hp_potion(to_string(user.getHpPotions().size()).c_str(), d.GetAllocator());

    Value key_str_potion("str-potion", d.GetAllocator());
    Value value_str_potion(to_string(user.getStrPotions().size()).c_str(), d.GetAllocator());

    json.AddMember(key_id, value_id, d.GetAllocator());
    json.AddMember(key_hp, value_hp, d.GetAllocator());
    json.AddMember(key_str, value_str, d.GetAllocator());
    json.AddMember(key_x, value_x, d.GetAllocator());
    json.AddMember(key_y, value_y, d.GetAllocator());
    json.AddMember(key_hp_potion, value_hp_potion, d.GetAllocator());
    json.AddMember(key_str_potion, value_str_potion, d.GetAllocator());

    return json;
}

void JsonBuilder::clean() {
    d.Swap(Value(kObjectType).Move());
}
