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

bool utils::code::decode_message(std::string in_messaage, std::string &out_messsage) {
    int ret = WS_OPENING_FRAME;
    const char *frameData = in_messaage.c_str();
    const int frameLength = in_messaage.size();


    if (frameLength < 2) {
        ret = WS_ERROR_FRAME;
    }
    //拓展位暂不处理
    if ((frameData[0] & 0x70) != 0x0) {
        ret = WS_ERROR_FRAME;
    }

    // fin位: 为1表示已接收完整报文, 为0表示继续监听后续报文
    ret = (frameData[0] & 0x80);
    if ((frameData[0] & 0x80) != 0x80) {
        ret = WS_ERROR_FRAME;
    }

    // mask位, 为1表示数据被加密
    if ((frameData[1] & 0x80) != 0x80) {
        ret = WS_ERROR_FRAME;
    }

    uint16_t payloadLength = 0;
    uint8_t payloadFieldExtraBytes = 0;
    uint8_t opcode = static_cast<uint8_t >(in_messaage[0] & 0x0f);

    switch (opcode) {
        case WS_TEXT_FRAME: {
            payloadLength = static_cast<uint8_t >(in_messaage[1] & 0x7f);
            if (payloadLength == 0x7e) {
                uint16_t payloadLength16b = 0;
                payloadFieldExtraBytes = 2;
                memcpy(&payloadLength16b, &frameData[2], payloadFieldExtraBytes);
                payloadLength = ntohs(payloadLength16b);
            } else if (payloadLength == 0x7f) {
                // 数据过长,暂不支持
                ret = WS_ERROR_FRAME;
            }
            break;
        }
        case WS_CLOSING_FRAME:
            return WS_CLOSING_FRAME;
//            ret = WS_CLOSING_FRAME;
//            break;
        case WS_BINARY_FRAME :
        case WS_PING_FRAME:
        case WS_PONG_FRAME:
            //暂不处理
            break;
        default:
            ret = WS_ERROR_FRAME;

    }


    if ((ret != WS_ERROR_FRAME) && (payloadLength > 0)) {
        // header: 2字节, masking key: 4字节
        const char *maskingKey = &frameData[2 + payloadFieldExtraBytes];
        char *payloadData = new char[payloadLength + 1];
        memset(payloadData, 0, payloadLength + 1);
        memcpy(payloadData, &frameData[2 + payloadFieldExtraBytes + 4], payloadLength);
        for (int i = 0; i < payloadLength; i++) {
            payloadData[i] = payloadData[i] ^ maskingKey[i % 4];
        }
        out_messsage = payloadData;
        delete[] payloadData;
    }

    return ret;

}

bool utils::code::encode_message() {
    return true;
}
