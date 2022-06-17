//
// Created by yunling on 2022/6/15.
//

#include "epoll_utils.h"


bool epoll_utils::epoll_add(int conn, uint32_t _event) {
    struct epoll_event event;
    event.events = _event;
    event.data.fd = conn;
    epoll_ctl(epfd, EPOLL_CTL_ADD, conn, &event);
}

bool epoll_utils::epoll_delete(int conn) {
    epoll_ctl(epfd, EPOLL_CTL_DEL, conn, NULL);
}


bool epoll_utils::epoll_init() {
    epfd = epoll_create(10); //创建epoll数组
}


bool epoll_utils::epoll_poccess(fun_poccess poccess) {
    while (true) {
        int nfds = epoll_wait(epfd, events, EVENT_SIZE, 5);
        for (int i = 0; i < nfds; i++) {
            poccess(events[i]);
        }
    }
    return true;
}


