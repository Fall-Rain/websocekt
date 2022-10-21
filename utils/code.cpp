//
// Created by yunling on 2022/6/14.
//

#include <netinet/in.h>
#include "code.h"


bool
utils::code::encode_accept(std::string *input, std::string *output) {
    *input += MAGIC_KEY;
    SHA1 sha;
    unsigned int message_digest[5];
    sha.Reset();
    sha << input->c_str();
    sha.Result(message_digest);
    for (int i = 0; i < 5; i++)
        message_digest[i] = htonl(message_digest[i]);
    *output = base64_encode(reinterpret_cast<const unsigned char *>(message_digest), 20);
    return true;
}

bool
utils::code::decode_accept(std::string input, std::map<std::string, std::string> *map) {
    std::vector<std::string> vec;
    boost::split(vec, input, boost::is_any_of("\r\n"), boost::token_compress_on);
    std::regex reg("(.*): (.*)");
    std::smatch cmatch;
    for (auto item = vec.begin()++; item != vec.end(); item++) {
        if (std::regex_match(*item, cmatch, reg)) {
            map->insert(std::pair<std::string, std::string>(cmatch[1], cmatch[2]));
        }
    }
    return true;
}

bool utils::code::decode_message() {
    return true;
}

bool utils::code::encode_message() {
    return true;
}
