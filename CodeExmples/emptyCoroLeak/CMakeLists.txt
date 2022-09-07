cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(emptyCoroLeak
        DESCRIPTION "emptyCoroLeak"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(emptyCoroLeak emptyCoro.cpp)
