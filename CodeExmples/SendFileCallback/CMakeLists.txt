cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(SendfileCallBack
        DESCRIPTION "SendfileCallBack"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(SendfileCallBack src/main.cpp src/FileSender.hpp src/FileSender.cpp)
target_link_libraries(SendfileCallBack asio::asio)