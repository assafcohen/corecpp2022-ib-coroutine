cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(emptyCoro
        DESCRIPTION "emptyCoro"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(emptyCoro emptyCoroDemo.cpp)
