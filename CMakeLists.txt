cmake_minimum_required(VERSION 3.16)
project(websocket)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.71.0 REQUIRED COMPONENTS regex)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(websocket main.cpp)
target_link_libraries(websocket Boost::regex)
