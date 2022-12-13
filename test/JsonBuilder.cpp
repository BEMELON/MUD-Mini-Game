//
// Created by BEMELON on 22. 12. 6.
//

#include "../server/header/rapidjson/document.h"
#include "../server/header/JsonBuilder.h"
#include "../server/header/rapidjson/stringbuffer.h"
#include "../server/header/rapidjson/prettywriter.h"

JsonBuilder::JsonBuilder() {
    d.SetObject();
};

JsonBuilder &JsonBuilder::add(const string& key, int value) {
    rapidjson::Value vName(rapidjson::kStringType);
    vName.SetString(key.c_str(), d.GetAllocator());

    rapidjson::Value vValue(rapidjson::kNumberType);
    vValue.SetInt(value);

    d.AddMember(vName, vValue, d.GetAllocator());

    return *this;
}

JsonBuilder &JsonBuilder::add(const string& key, const string& value) {
    rapidjson::Value vName(rapidjson::kStringType);
    vName.SetString(key.c_str(), d.GetAllocator());

    rapidjson::Value vValue(rapidjson::kStringType);
    vValue.SetString(value.c_str(), d.GetAllocator());

    d.AddMember(vName, vValue, d.GetAllocator());

    return *this;
}

string JsonBuilder::build() {
    rapidjson::StringBuffer strbuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strbuf);
    d.Accept(writer);

    return strbuf.GetString();
}