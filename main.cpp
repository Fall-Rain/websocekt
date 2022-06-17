#include "utils/socket_utils.h"
#include "utils/utils.h"
#include "utils/epoll_utils.h"

#define EVENT_SIZE 10

//int main() {
//    int server_socket = socket_utils::start_socket(8091); //构造socket
//    struct _event event, events[EVENT_SIZE]; //定义epoll信息
//    int epfd = epoll_create(10); //创建epoll数组
//    event.data.fd = server_socket;
//    event.events = EPOLLIN;
//    epoll_ctl(epfd, EPOLL_CTL_ADD, server_socket, &event); //将服务端的socket放入epoll里
//    while (true) {
//        int nfds = epoll_wait(epfd, events, EVENT_SIZE, 5); //等待连接
//        for (int i = 0; i < nfds; i++) { //循环去遍历
//            if (events[i].data.fd == server_socket) { //判断是否为连接服务端的socket，接受连接并将其加载到epoll里
//                struct sockaddr_in client_addr;
//                socklen_t client_len = sizeof(client_addr);
//                int conn = accept(server_socket, (struct sockaddr *) &client_addr, &client_len);
//                event.events = EPOLLIN;
//                event.data.fd = conn;
//                epoll_ctl(epfd, EPOLL_CTL_ADD, conn, &event);
//            } else if (events[i].events & EPOLLIN) { //当有socket的数据来临时，读取请求头，创建应答头，并返回给客户端
//                int conn = events[i].data.fd;
//                socket_utils::handshake(conn);
//            }
//        }
//    }
//}
int server_socket;

void poccess(epoll_event event) {
    if (event.data.fd == server_socket) { //判断是否为连接服务端的socket，接受连接并将其加载到epoll里
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int conn = accept(server_socket, (struct sockaddr *) &client_addr, &client_len);
        epoll_utils::epoll_add(conn, EPOLLIN);
    } else if (event.events & EPOLLIN) { //当有socket的数据来临时，读取请求头，创建应答头，并返回给客户端
        int conn = event.data.fd;
        socket_utils::handshake(conn);
    }
}

int main() {
    server_socket = socket_utils::start_socket(8090);
    epoll_utils::epoll_init();
    epoll_utils::epoll_add(server_socket, EPOLLIN);
    epoll_utils::epoll_poccess(poccess);
}