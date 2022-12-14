//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/BasicResponseDto.h"
#define RAPIDJSON_HAS_STDSTRING 1

BasicResponseDto::BasicResponseDto() {}

std::string BasicResponseDto::getJsonMsg() {
    return jsonBuilder.build();
}

IResponseDTO *BasicResponseDto::setStatus(const char *status) {
    this->msg = status;
    jsonBuilder.add("status", status);
    return this;
}

void BasicResponseDto::addUsers(list<User> users) {
    jsonBuilder.addUsers(users);
}

void BasicResponseDto::setUser(User user) {
    jsonBuilder.setUser(user);
}

