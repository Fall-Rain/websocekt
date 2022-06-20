//
// Created by yunling on 2022/6/15.
//

#include "epoll.h"

int utils::epoll::_epfd = 0;
epoll_event *utils::epoll::_events = new epoll_event[EVENT_SIZE];


bool utils::epoll::epoll_add(int conn, uint32_t _event) {
    struct epoll_event event;
    event.events = _event;
    event.data.fd = conn;
    epoll_ctl(_epfd, EPOLL_CTL_ADD, conn, &event);
    return true;
}

bool utils::epoll::epoll_delete(int conn) {
    epoll_ctl(_epfd, EPOLL_CTL_DEL, conn, NULL);
    return true;
}


bool utils::epoll::epoll_init() {
    _epfd = epoll_create(10); //创建epoll数组
    return true;
}


bool utils::epoll::epoll_poccess(fun_poccess poccess) {
    while (true) {
        int nfds = epoll_wait(_epfd, _events, EVENT_SIZE, 5);
        for (int i = 0; i < nfds; i++) {
            poccess(_events[i]);
        }
    }
    return true;
}


