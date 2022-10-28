//
// Created by yunling on 2022/6/14.
//

#include "socket.h"


bool Socket::start_socket(int port) {
    _server_socket = ::socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    int oldSocketFlag = fcntl(_server_socket, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(_server_socket, F_SETFL, newSocketFlag) == -1) {
        close(_server_socket);
        std::cout << "非阻塞失败" << std::endl;
        exit(0);
    }
    int server_len = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    std::cout << "bind：" << bind(_server_socket, (struct sockaddr *) &server_addr, server_len) << std::endl;
    std::cout << "listen：" << listen(_server_socket, 5) << std::endl;
    epoll::epoll_add(this->epfd, this->_server_socket, EPOLLIN);
    Accept();
    return true;
}

bool Socket::handshake(epoll_event event) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int conn = accept(this->_server_socket, (struct sockaddr *) &client_addr, &client_len);
    char buffer[BUF_SIZE];
    memset(buffer, 0, sizeof(buffer));
    read(conn, buffer, BUF_SIZE);
//    std::cout << buffer << std::endl;
    std::map<std::string, std::string> map;
    utils::code::decode_accept(buffer, &map);
//    std::string key = map.find("Sec-WebSocket-Key")->second + MAGIC_KEY;
    std::string sec_websocket_accept;
    utils::code::encode_accept(&map.find("Sec-WebSocket-Key")->second, &sec_websocket_accept);
    std::string buff =
            "HTTP/1.1 101 Switching Protocols\r\n"
            "Upgrade: websocket\r\n"
            "Connection: Upgrade\r\n"
            "Sec-WebSocket-Accept: " + sec_websocket_accept + "\r\n\r\n";
    write(conn, buff.c_str(), buff.length());
    std::string message;
//    utils::code::encode_message("", message, WS_PING_FRAME);
//    Socket::Write(conn, message);
    utils::code::encode_message("你好,欢迎登录", message, WS_TEXT_FRAME);
    Socket::Write(conn, message);
    epoll::epoll_add(this->epfd, conn, EPOLLIN);
    return true;
}

bool Socket::interception(fun_poccess poccess) {
    this->poccess.push_back(poccess);
    return true;
}

Socket::Socket() {
    this->epfd = epoll_create(10);
    this->events = new epoll_event[EVENT_SIZE];
}


int Socket::Accept() {
    while (true) {
        int nfds = epoll_wait(this->epfd, this->events, EVENT_SIZE, 5);
        if (nfds < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                break;
            }
        }
        for (int i = 0; i < nfds; i++) {
            if (this->events[i].data.fd == this->_server_socket) {
                handshake(events[i]);
            } else {
                for (const auto &item: poccess)
                    item(events[i]);
            }
        }
    }
    return 0;
}


void Socket::Close(int conn) {
    epoll::epoll_delete(this->epfd, conn);
    close(conn);
}

std::string Socket::Read(int fd) {
    char buffer[BUF_SIZE];
    memset(buffer, 0, sizeof(buffer));
    read(fd, buffer, BUF_SIZE);
    return buffer;
}

bool Socket::Write(int fd, std::string message) {
    write(fd, message.c_str(), message.size());
    return true;
}