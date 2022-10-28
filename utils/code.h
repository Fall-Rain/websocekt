//
// Created by yunling on 2022/6/14.
//

#ifndef WEBSOCKET_CODE_H
#define WEBSOCKET_CODE_H

#include <vector>
#include "string"
#include "map"
#include "boost/algorithm/string.hpp"
#include <regex>
#include "sha1.h"
#include "base64.h"

#define WS_EMPTY_FRAME  0xF0
#define WS_ERROR_FRAME  0xF1
#define WS_TEXT_FRAME  0x01
#define WS_BINARY_FRAME  0x02
#define WS_PING_FRAME  0x09
#define WS_PONG_FRAME  0x0A
#define WS_OPENING_FRAME  0xF3
#define WS_CLOSING_FRAME  0x08
#define MAGIC_KEY "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
namespace utils {
    class code {
    public:
        static bool
        encode_accept(std::string *input, std::string *output);

        static bool
        decode_accept(std::string input, std::map<std::string, std::string> *map);

        static int
        encode_message(std::string in_messaage, std::string &out_message, uint8_t frameType);

        static int
        decode_message(std::string in_messaage, std::string &out_messsage);
    };
};


#endif //WEBSOCKET_CODE_H
