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

    typedef bool (*fun_conditions)(epoll_event event);

    typedef void (*fun_poccess)(int conn);

    static std::map<fun_conditions,fun_poccess> poccess_map;
public:

    static bool
    epoll_add(int conn, uint32_t events);

    static bool
    epoll_delete(int conn);

    static bool
    epoll_init();

    static bool
    epoll_register(fun_conditions conditions,fun_poccess poccess);

    static bool
    epoll_wait_notify();
};


#endif //WEBSOCKET_EPOLL_UTILS_H
