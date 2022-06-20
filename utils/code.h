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

#define MAGIC_KEY "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

namespace utils {
    class code {
    public:
        static bool
        encode_accept(std::string *input, std::string *output);

        static bool
        decode_accept(std::string input, std::map<std::string, std::string> *map);

        static bool
        encode_message();

        static bool
        decode_message();
    };
};


#endif //WEBSOCKET_CODE_H
