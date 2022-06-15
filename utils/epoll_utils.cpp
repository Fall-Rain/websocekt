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


bool epoll_utils::epoll_register(fun_conditions conditions, fun_poccess poccess) {
    poccess_map.insert(std::pair<fun_conditions, fun_poccess>(conditions, poccess));
}


bool epoll_utils::epoll_wait_notify() {
    while (true) {
        int nfds = epoll_wait(epfd, events, EVENT_SIZE, 5);
        for (int i = 0; i < nfds; i++) {
            for (auto &item: poccess_map) {
                if (item.first(events[i])) item.second(events[i].data.fd);
            }
        }
    }
}
