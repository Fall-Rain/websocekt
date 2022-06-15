//
// Created by yunling on 2022/6/14.
//

#include "socket_utils.h"
#include "utils.h"

int socket_utils::start_socket(int port) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    int oldSocketFlag = fcntl(server_socket, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(server_socket, F_SETFL, newSocketFlag) == -1) {
        close(server_socket);
        std::cout << "非阻塞失败" << std::endl;
        exit(0);
    }
    int server_len = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    std::cout << "bind：" << bind(server_socket, (struct sockaddr *) &server_addr, server_len) << std::endl;
    std::cout << "listen：" << listen(server_socket, 5) << std::endl;
    return server_socket;
}

bool socket_utils::handshake(int conn) {
    char buffer[BUF_SIZE];
    memset(buffer, 0, sizeof(buffer));
    read(conn, buffer, BUF_SIZE);
    std::cout << buffer << std::endl;
    auto bufflist = utils::split(buffer, "\r\n");
    std::map<std::string, std::string> map = utils::split(bufflist.begin() + 1, bufflist.end(), ":");
    std::string key = map.find("Sec-WebSocket-Key")->second + MAGIC_KEY;
    std::string sec_websocket_accept;
    utils::encode(&map.find("Sec-WebSocket-Key")->second, &sec_websocket_accept);
    std::string buff =
            "HTTP/1.1 101 Switching Protocols\r\n"
            "Upgrade: websocket\r\n"
            "Connection: Upgrade\r\n"
            "Sec-WebSocket-Accept: " + sec_websocket_accept + "\r\n\r\n";
    write(conn, buff.c_str(), buff.length());
    return true;
}