cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(SendfileBlocking
        DESCRIPTION "SendfileBlocking"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(SendfileBlocking src/main.cpp src/FileSender.hpp src/FileSender.cpp)
target_link_libraries(SendfileBlocking fmt::fmt Boost::Boost)