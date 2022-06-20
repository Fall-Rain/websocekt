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
namespace utils {
    class socket {
    private:
        static int _server_socket;
    public:
        static bool start_socket(int port);

        static bool handshake(int conn);

        static int getServerSocket();
    };
}


#endif //WEBSOCKET_SOCKET_H
