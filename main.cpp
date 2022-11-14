#include "utils/socket.h"
#include "utils/code.h"
#include "utils/epoll.h"

#define EVENT_SIZE 10


bool ws_binary_frame(std::string message, int ret, int fd) {
    return true;
}

bool ws_pong_frame(std::string message, int ret, int fd) {
    if (ret != WS_PONG_FRAME) return false;
    std::string socket_message;
    utils::code::encode_message("", socket_message, WS_PING_FRAME);
    std::cout << "pong" << std::endl;
    Socket::Write(fd, socket_message);
    return true;
}

bool ws_ping_frame(std::string message, int ret, int fd) {
    if (ret != WS_PING_FRAME) return false;
    std::string socket_message;
    utils::code::encode_message("", socket_message, WS_PONG_FRAME);
    std::cout << "ping" << std::endl;
    Socket::Write(fd, socket_message);
    return true;
}

bool ws_closing_frame(std::string message, int ret, int fd) {
    if (ret != WS_CLOSING_FRAME) return false;
    Socket::Close(fd);
    return true;
}

bool ws_error_frame(std::string message, int ret, int fd) {
    if (ret != WS_ERROR_FRAME) return false;
    Socket::Close(fd);
    return true;
}

bool ws_text_frame(std::string message, int ret, int fd) {
    if (ret != WS_TEXT_FRAME) return false;
    std::cout << message << std::endl;
    std::string socket_message;
    utils::code::encode_message(message, socket_message, WS_TEXT_FRAME);
    Socket::Write(fd, socket_message);
    return true;
}

bool after_handshake(int fd) {
    std::string message;
    utils::code::encode_message("你好,欢迎登录", message, WS_TEXT_FRAME);
    Socket::Write(fd, message);
    return true;
}

int main() {
    Socket *sock = new Socket();
    sock->set_after_handshake(after_handshake);
    sock->interception(ws_text_frame);
    sock->interception(ws_error_frame);
    sock->interception(ws_closing_frame);
    sock->interception(ws_ping_frame);
    sock->interception(ws_pong_frame);
    sock->interception(ws_binary_frame);
    sock->start_socket(8090);
}