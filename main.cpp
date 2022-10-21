#include "utils/socket.h"
#include "utils/code.h"
#include "utils/epoll.h"

#define EVENT_SIZE 10
int server_socket;
Socket *sock;


bool poccess(epoll_event event) {
    if (!event.events & EPOLLIN) {
        return true;
    }
    unsigned int bytes[16];
    char buffer[BUF_SIZE];
    memset(buffer, 0, sizeof(buffer));
    read(event.data.fd, buffer, BUF_SIZE);
    std::cout << buffer << std::endl;
    sock->Close(event.data.fd);
    return true;
//    write(conn, buffer, BUF_SIZE);
//    close(conn);
}

int main() {
    sock = new Socket();
    sock->interception(poccess);
    sock->start_socket(8090);
}