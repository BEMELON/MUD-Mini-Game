//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/BasicResponseDto.h"
#define RAPIDJSON_HAS_STDSTRING 1
#include "../header/rapidjson/stringbuffer.h"
#include "../header/rapidjson/prettywriter.h"

BasicResponseDto::BasicResponseDto() {}

std::string BasicResponseDto::getJsonMsg() {
    return this->json_msg;
}

IResponseDTO *BasicResponseDto::setStatus(const char *status) {
    this->msg = status;

    rapidjson::Document d(rapidjson::kObjectType);
    rapidjson::Value json_msg(status, d.GetAllocator());

    d.AddMember("status", json_msg, d.GetAllocator());

    rapidjson::StringBuffer strbuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strbuf);
    d.Accept(writer);

    this->json_msg = strbuf.GetString();
    return this;
}