//
// Created by yunling on 2022/6/15.
//

#include "epoll.h"


bool epoll::epoll_add(int epfd, int conn, uint32_t events) {
    struct epoll_event event;
    event.events = events;
    event.data.fd = conn;
    epoll_ctl(epfd, EPOLL_CTL_ADD, conn, &event);
    return true;
}


bool epoll::epoll_delete(int epfd, int conn) {
    epoll_ctl(epfd, EPOLL_CTL_DEL, conn, NULL);
    return true;
}




