//
// Created by yunling on 2022/6/15.
//

#ifndef WEBSOCKET_EPOLL_UTILS_H
#define WEBSOCKET_EPOLL_UTILS_H

#include <sys/epoll.h>
#include "iostream"
#include "map"

#define EVENT_SIZE 10

class epoll_utils {
private:
    static epoll_event events[EVENT_SIZE]; //定义epoll信息
    static int epfd;

    typedef void (*fun_poccess)(epoll_event event);

public:

    static bool
    epoll_add(int conn, uint32_t events);

    static bool
    epoll_delete(int conn);

    static bool
    epoll_init();

    static bool
    epoll_poccess(fun_poccess poccess);
};


#endif //WEBSOCKET_EPOLL_UTILS_H
