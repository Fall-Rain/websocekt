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
    std::string result;
    int ret = utils::code::decode_message(buffer, result);
    if (ret == WS_ERROR_FRAME) {
        sock->Close(event.data.fd);
        return false;
    }
    if (ret == WS_CLOSING_FRAME) {
        sock->Close(event.data.fd);
        return true;
    }
    std::cout << result << std::endl;
//    sock->Close(event.data.fd);
    return true;
//    write(conn, buffer, BUF_SIZE);
//    close(conn);
}

int main() {
    sock = new Socket();
    sock->interception(poccess);
    sock->start_socket(8090);
//    uint8_t opcode = 0xA8 & 0x0f;
}