cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(SendfileCoroutine
        DESCRIPTION "SendfileCoroutine"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(SendfileCoroutine src/main.cpp src/FileSender.hpp src/FileSender.cpp)
target_link_libraries(SendfileCoroutine asio::asio)