//
// Created by yunling on 2022/6/14.
//

#include <netinet/in.h>
#include "utils.h"

typedef bool b;

[[maybe_unused]] std::vector<std::string> utils::split(std::string str, std::string pred) {
    std::vector<std::string> result;
    boost::split(result, str, boost::is_any_of(pred), boost::token_compress_on);
    return result;
}

[[maybe_unused]] std::map<std::string, std::string>
utils::split(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end, std::string pred) {
    std::map<std::string, std::string> result;
    std::regex reg("(.*): (.*)");
    std::smatch cmatch;
    for (auto item = begin; item != end; item++) {
        if (std::regex_match(*item, cmatch, reg)) {
            result.insert(std::pair<std::string, std::string>(cmatch[1], cmatch[2]));
        }
    }
    return result;
}

bool
utils::encode(std::string *input, std::string *output) {
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