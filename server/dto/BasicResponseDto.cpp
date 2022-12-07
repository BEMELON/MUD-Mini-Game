//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/BasicResponseDto.h"
#define RAPIDJSON_HAS_STDSTRING 1
#include "../header/JsonBuilder.h"

BasicResponseDto::BasicResponseDto() {}

std::string BasicResponseDto::getJsonMsg() {
    return this->json_msg;
}

IResponseDTO *BasicResponseDto::setStatus(const char *status) {
    this->msg = status;

    JsonBuilder responseBuilder = JsonBuilder();
    this->json_msg = responseBuilder.add("status", status).build();

    return this;
}