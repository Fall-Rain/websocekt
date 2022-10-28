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
    std::string socket_message = Socket::Read(event.data.fd);
    std::string message;
    int ret = utils::code::decode_message(socket_message.c_str(), message);
    switch (ret) {
        case WS_OPENING_FRAME:
            std::cout << message << std::endl;
            utils::code::encode_message(message, socket_message, WS_TEXT_FRAME);
//            Socket::Write(event.data.fd, socket_message);
//            std::cout << message << std::endl;
            break;
        case WS_ERROR_FRAME:
            sock->Close(event.data.fd);
            return false;
        case WS_CLOSING_FRAME:
            sock->Close(event.data.fd);
            return true;
        case WS_PING_FRAME:
            utils::code::encode_message("", socket_message, WS_PONG_FRAME);
            std::cout << "ping" << std::endl;
            break;
        case WS_PONG_FRAME:
            utils::code::encode_message("", socket_message, WS_PING_FRAME);
            std::cout << "pong" << std::endl;
            break;
    }
    Socket::Write(event.data.fd, socket_message);
    return true;
}

int main() {
    sock = new Socket();
    sock->interception(poccess);
    sock->start_socket(8090);
//    uint8_t opcode = 0xA8 & 0x0f;
}