//
// Created by yunling on 2022/6/14.
//

#ifndef WEBSOCKET_UTILS_H
#define WEBSOCKET_UTILS_H

#include <vector>
#include "string"
#include "map"
#include "boost/algorithm/string.hpp"
#include <regex>
#include "sha1.h"
#include "base64.h"

#define MAGIC_KEY "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

class utils {
public:
    static std::vector<std::string>
    split(
            std::string str,
            std::string pred
    );

    static std::map<std::string, std::string>
    split(
            std::vector<std::string>::iterator begin,
            std::vector<std::string>::iterator end,
            std::string pred
    );

    static bool
    encode(std::string *input, std::string *output);
};


#endif //WEBSOCKET_UTILS_H
