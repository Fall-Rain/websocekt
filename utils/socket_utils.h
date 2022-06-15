//
// Created by yunling on 2022/6/14.
//

#ifndef WEBSOCKET_SOCKET_UTILS_H
#define WEBSOCKET_SOCKET_UTILS_H

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

#define BUF_SIZE 4096

class socket_utils {
public:
    static int start_socket(int port);

    static bool handshake(int conn);
};


#endif //WEBSOCKET_SOCKET_UTILS_H
