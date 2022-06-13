#include <iostream>
//#include "boost/regex.hpp"
#include "string"
#include "boost/algorithm/string.hpp"

int main() {
    std::string str = "hello,word,nihao,haoba,woxihuan";
    std::vector<std::string> vec;
    boost::split(vec, str, boost::is_any_of(","), boost::token_compress_on);
    for (const auto &item: vec)
        std::cout << item << std::endl;
}
