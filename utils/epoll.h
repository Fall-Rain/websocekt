//
// Created by yunling on 2022/6/15.
//

#ifndef WEBSOCKET_EPOLL_H
#define WEBSOCKET_EPOLL_H

#include <sys/epoll.h>
#include "iostream"
#include "map"

#define EVENT_SIZE 10

class epoll {
public:

    static bool
    epoll_add(int epfd, int conn, uint32_t events);

    static bool
    epoll_delete(int epfd, int conn);
};


#endif //WEBSOCKET_EPOLL_H
