//
// Created by BEMELON on 22. 12. 6.
//

#include "../header/ResponseDto.h"
#define RAPIDJSON_HAS_STDSTRING 1

ResponseDto::ResponseDto() {}

std::string ResponseDto::getJsonMsg() {
    return jsonBuilder.build();
}

IResponseDTO *ResponseDto::setStatus(const char *status) {
    this->msg = status;
    jsonBuilder.add("status", status);
    return this;
}

void ResponseDto::addUsers(list<User *> users) {
    jsonBuilder.addUsers(users);
}

void ResponseDto::setUser(User user) {
    jsonBuilder.setUser(user);
}

void ResponseDto::clean() {
    jsonBuilder.clean();
}

