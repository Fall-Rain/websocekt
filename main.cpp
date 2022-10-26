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
    std::string message = Socket::Read(event.data.fd);
    std::string result, message1;
    int ret = utils::code::decode_message(message.c_str(), result);
    if (ret == WS_ERROR_FRAME) {
        sock->Close(event.data.fd);
        return false;
    }
    if (ret == WS_CLOSING_FRAME) {
        sock->Close(event.data.fd);
        return true;
    }
    utils::code::encode_message(result, message1);
    Socket::Write(event.data.fd, message1);
    std::cout << result << std::endl;
    return true;
}

int main() {
    sock = new Socket();
    sock->interception(poccess);
    sock->start_socket(8090);
//    uint8_t opcode = 0xA8 & 0x0f;
}