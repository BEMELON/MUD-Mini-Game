//
// Created by BEMELON on 22. 12. 13.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "gtest/gtest.h"
#include "../server/header/JsonBuilder.h"
#include "../server/header/JsonParser.h"

int getConn() {
    int fd;
    struct sockaddr_in server;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);
    server.sin_family = AF_INET;

    int ret = connect(fd, reinterpret_cast<const sockaddr *>(&server), sizeof(struct sockaddr_in));

    if (ret < 0) {
        exit(-1);
    }
    return fd;
}

void closeConn(int fd) {
    close(fd);
}

TEST(USER_CONTROLLER, GET_ROOT) {
    int fd = getConn();
    char buffer[256];
    memset(buffer, 0, 256);

    JsonBuilder jsonBuilder = JsonBuilder();
    jsonBuilder.add("Request URL", "/user");
    std::string json = jsonBuilder.build();
    send(fd, json.c_str(), json.length(), 0);


    recv(fd, buffer, 256, 0);
    JsonParser jsonParser = JsonParser();
    jsonParser.parse(buffer);
    EXPECT_TRUE(jsonParser.has("status"));
    EXPECT_STREQ(jsonParser.getString("status").c_str(), "success");

    closeConn(fd);
}

TEST(USER_CONTROLLER, POST_LOGIN) {
    int fd = getConn();
    char buffer[256];
    memset(buffer, 0, 256);

    JsonBuilder jsonBuilder = JsonBuilder();
    jsonBuilder.add("Request URL", "/user/login");
    std::string json = jsonBuilder.build();
    send(fd, json.c_str(), json.length(), 0);


    recv(fd, buffer, 256, 0);
    JsonParser jsonParser = JsonParser();
    jsonParser.parse(buffer);
    EXPECT_TRUE(jsonParser.has("status"));
    EXPECT_STREQ(jsonParser.getString("status").c_str(), "success");

    closeConn(fd);
}

TEST(USER_CONTROLLER, GET_USER_INFO) {
    int fd = getConn();
    char buffer[256];
    memset(buffer, 0, 256);

    JsonBuilder jsonBuilder = JsonBuilder();
    jsonBuilder.add("Request URL", "/user/1");
    std::string json = jsonBuilder.build();
    send(fd, json.c_str(), json.length(), 0);


    recv(fd, buffer, 256, 0);
    JsonParser jsonParser = JsonParser();
    jsonParser.parse(buffer);
    EXPECT_TRUE(jsonParser.has("status"));
    EXPECT_STREQ(jsonParser.getString("status").c_str(), "success");

    closeConn(fd);
}

TEST(USER_CONTROLLER, MOVE_USER) {
    int fd = getConn();
    char buffer[256];
    memset(buffer, 0, 256);

    JsonBuilder jsonBuilder = JsonBuilder();
    jsonBuilder.add("Request URL", "/user/1/move");
    std::string json = jsonBuilder.build();
    send(fd, json.c_str(), json.length(), 0);


    recv(fd, buffer, 256, 0);
    JsonParser jsonParser = JsonParser();
    jsonParser.parse(buffer);
    EXPECT_TRUE(jsonParser.has("status"));
    EXPECT_STREQ(jsonParser.getString("status").c_str(), "success");

    closeConn(fd);
}

TEST(USER_CONTROLLER, USER_ATTACK) {
    int fd = getConn();
    char buffer[256];
    memset(buffer, 0, 256);

    JsonBuilder jsonBuilder = JsonBuilder();
    jsonBuilder.add("Request URL", "/user/1/attack");
    std::string json = jsonBuilder.build();
    send(fd, json.c_str(), json.length(), 0);


    recv(fd, buffer, 256, 0);
    JsonParser jsonParser = JsonParser();
    jsonParser.parse(buffer);
    EXPECT_TRUE(jsonParser.has("status"));
    EXPECT_STREQ(jsonParser.getString("status").c_str(), "success");

    closeConn(fd);
}

TEST(USER_CONTROLLER, USER_SEND_MSG) {
    int fd = getConn();
    char buffer[256];
    memset(buffer, 0, 256);

    JsonBuilder jsonBuilder = JsonBuilder();
    jsonBuilder.add("Request URL", "/user/1/sendMsg");
    std::string json = jsonBuilder.build();
    send(fd, json.c_str(), json.length(), 0);


    recv(fd, buffer, 256, 0);
    JsonParser jsonParser = JsonParser();
    jsonParser.parse(buffer);
    EXPECT_TRUE(jsonParser.has("status"));
    EXPECT_STREQ(jsonParser.getString("status").c_str(), "success");

    closeConn(fd);
}
