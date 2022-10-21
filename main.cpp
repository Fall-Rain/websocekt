#include "utils/socket.h"
#include "utils/code.h"
#include "utils/epoll.h"

#define EVENT_SIZE 10
int server_socket;

void poccess(int conn) {
    unsigned int bytes[16];
    char buffer[BUF_SIZE];
    memset(buffer, 0, sizeof(buffer));
    read(conn, buffer, BUF_SIZE);
    std::cout << buffer << std::endl;
//    write(conn, buffer, BUF_SIZE);
//    close(conn);
}

int main() {
    Socket *sock = new Socket();
    sock->interception(poccess);
    sock->start_socket(8090);
}