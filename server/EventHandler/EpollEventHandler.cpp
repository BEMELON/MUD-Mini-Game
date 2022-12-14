//
// Created by BEMELON on 22. 12. 15.
//

#include "../header/EpollEventHandler.h"
#include <sys/epoll.h>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/tcp.h>

using namespace std;
void EpollEventHandler::listen(int port) {
    this->port = port;
    int epfd, passive, flags, option;
    char msg[256];
    struct sockaddr_in server;
    struct epoll_event events;

    // Passive socket
    if ((passive = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        this->logger->logSysErrorMsg("socket");

    // reuse-address
    if ((flags = setsockopt(passive, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option))) < 0)
        this->logger->logSysErrorMsg("setsockopt");

    // Nagle Algorithm off
    int nValue = 1;
    if (setsockopt(passive, IPPROTO_TCP, TCP_NODELAY, &nValue, sizeof(nValue)) < 0)
        this->logger->logSysErrorMsg("setsockopt(TCP_NODELAY)");

    // set server fd as NON_BLOCK
    flags = fcntl(passive, F_GETFL);
    flags |= O_NONBLOCK;
    if (fcntl(passive, F_SETFL, flags) < 0)
        this->logger->logSysErrorMsg("set fcntl");

    // Set Server struct
    ::memset(&server, 0, sizeof(server));
    server.sin_port = htons(this->port);
    server.sin_addr.s_addr = inet_addr("0.0.0.0");
    server.sin_family = AF_INET;

    // Bind socket
    if (bind(passive, (const struct sockaddr *)&server, sizeof(server)) < 0)
        this->logger->logSysErrorMsg("Bind");

    // Listen
    if (::listen(passive, 15) < 0)
        this->logger->logSysErrorMsg("Listen");

    // Create EPOLL
    if ((epfd = epoll_create(1024)) < 0)
        this->logger->logSysErrorMsg("epoll_create");

    // Set event
    events.events = EPOLLIN | EPOLLET;
    events.data.fd = passive;

    // Add Epoll Event
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, passive, &events) < 0)
        this->logger->logSysErrorMsg("epoll_ctl");

    /**
     * timeout = -1, Blocking
     *            0, No-Wait
     *            0 < N, Wait for n seconds
     */
    int                        MAX_EVENTS = 1024;
    struct epoll_event        epoll_events[MAX_EVENTS];
    int                        event_count;
    int                        timeout = -1;

    this->logger->logInfoMsg("[Init] EpollEventHandler initialized");
    ::memset(msg, 0, 256);
    ::sprintf(msg, "[DEBUG] Server started with port %d", this->port);
    this->logger->logInfoMsg(msg);
    while (true) {
        event_count = epoll_wait(epfd, epoll_events, MAX_EVENTS, timeout); // Blocking

        if (event_count < 0)
            this->logger->logSysErrorMsg("epoll_wait error");

        for(int i = 0; i < event_count; i++) {
            if (epoll_events[i].data.fd == passive) {
                int active;
                socklen_t len;
                struct sockaddr_in client;

                this->logger->logInfoMsg("[DEBUG] Event dispatched for new connection");
                ::memset(&client, 0 ,sizeof(client));
                len = 0;
                if ((active = accept(passive, (struct sockaddr *) &client, &len)) < 0)
                    this->logger->logSysErrorMsg("accept");

                // client fd Non-Blocking Socket으로 설정. Edge Trigger 사용하기 위해 설정.
                int flags = fcntl(active, F_GETFL);
                flags |= O_NONBLOCK;

                // Set NON_BLOCK
                if (fcntl(active, F_SETFL, flags) < 0)
                    this->logger->logSysErrorMsg("client fcntl");


                // 클라이언트 fd, epoll 에 등록
                struct epoll_event events;
                events.events = EPOLLIN | EPOLLET;
                events.data.fd = active;

                if (epoll_ctl(epfd, EPOLL_CTL_ADD, active, &events) < 0)
                    this->logger->logSysErrorMsg("client epoll_ctl");

            } else {
                // epoll에 등록 된 클라이언트들의 send data 처리
                char buffer[256];
                JsonParser jsonParser = JsonParser();
                int active;

                // set fd
                active = epoll_events[i].data.fd;

                memset(buffer, 0, 256);
                if (recv(active, buffer, 256, 0) < 0)
                    this->logger->logSysErrorMsg("Read failed");

                if (::strlen(buffer) == 0) {
                    this->logger->logInfoMsg("[DEBUG] Client has been terminated");
                    close(active);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, active, NULL);
                } else {
                    jsonParser.parse(buffer);

                    string url = jsonParser.getString("Request URL"); // /user/create
                    string root = getRoot(url);
                    auto fn = this->router.find(root)->second;
                    IController *controller = this->controller.find(root)->second;

                    this->requestDto->setBody(buffer);
                    this->responseDto->clean();
                    IResponseDTO* res = (controller->*fn)(this->requestDto, this->responseDto);

                    if (send(active, res->getJsonMsg().c_str(), res->getJsonMsg().size(), 0) < 0)
                        this->logger->logSysErrorMsg("Send Error");
                }
            }
        }
    }
}


void
EpollEventHandler::addRoute(std::string path, IResponseDTO *(IController::*fn_router)(IRequestDTO *, IResponseDTO *), IController *caller) {
    this->router.insert(std::make_pair(path, fn_router));
    this->controller.insert(std::make_pair(path, caller));
}

string EpollEventHandler::getRoot(const string& path) {
    int first_slash = path.find('/', 0);
    int second_slash = path.find('/', first_slash + 1);

    if (second_slash == string::npos)
        return path.substr(first_slash);
    else
        return path.substr(first_slash, second_slash - first_slash);
}
