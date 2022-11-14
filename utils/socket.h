//
// Created by yunling on 2022/6/14.
//

#ifndef WEBSOCKET_SOCKET_H
#define WEBSOCKET_SOCKET_H

#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include "stdio.h"
#include "boost/algorithm/string.hpp"
#include <fcntl.h>
#include "iostream"
#include "map"
#include "code.h"
#include "epoll.h"

#define BUF_SIZE 4096

class Socket {
private:

    typedef bool (*fun_poccess)(std::string message, int ret, int fd);

    typedef bool (*fun_after_handshake)(int fd);

    std::vector<fun_poccess> poccess;
    fun_after_handshake after_handshake;

    int _server_socket;

    epoll_event *events; //定义epoll信息
    static int epfd;
public:
    Socket();

    bool set_after_handshake(fun_after_handshake poccess);

    bool
    interception(fun_poccess poccess);

    bool start_socket(int port);

    bool handshake(epoll_event event);

    int Accept();

    static
    void Close(int conn);

    static
    bool Write(int fd, std::string message);

    static
    std::string Read(int fd);
};


#endif //WEBSOCKET_SOCKET_H
