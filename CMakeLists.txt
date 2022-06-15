cmake_minimum_required(VERSION 3.16)
project(websocket)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.71.0 REQUIRED COMPONENTS regex)
find_package(OpenSSL REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


add_executable(websocket main.cpp utils/utils.cpp utils/utils.h utils/socket_utils.cpp utils/socket_utils.h utils/base64.cpp utils/base64.h utils/sha1.cpp utils/sha1.h utils/epoll_utils.cpp utils/epoll_utils.h)
target_link_libraries(websocket Boost::regex OpenSSL::Crypto OpenSSL::SSL)
