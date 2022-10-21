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
    typedef void (*fun_poccess)(int conn);

    fun_poccess poccess;

    int _server_socket;

    epoll_event *events; //定义epoll信息
    int epfd;
public:
    Socket();

    bool
    interception(fun_poccess poccess);

    bool start_socket(int port);

    bool handshake(int conn);

    int Accept();
};


#endif //WEBSOCKET_SOCKET_H
