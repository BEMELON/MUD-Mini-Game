//
// Created by BEMELON on 22. 12. 15.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "gtest/gtest.h"
#include "../server/header/JsonBuilder.h"
#include "../server/header/JsonParser.h"

static int getConn() {
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

static void closeConn(int fd) {
    close(fd);
}

TEST(HEALTH_CONTORLLER, PingPong) {
    int fd = getConn();
    char buffer[256];

    JsonBuilder jsonBuilder = JsonBuilder();
    jsonBuilder.add("Request URL", "/health");
    std::string json = jsonBuilder.build();

    while (1) {

        send(fd, json.c_str(), json.length(), 0);

        ::memset(buffer, 0, 256);
        recv(fd, buffer, 256, 0);
        cout << buffer << endl;

        JsonParser jsonParser = JsonParser();
        jsonParser.parse(buffer);
        EXPECT_TRUE(jsonParser.has("status"));
        EXPECT_STREQ(jsonParser.getString("status").c_str(), "success");

        sleep(1);
    }

    closeConn(fd);
}
