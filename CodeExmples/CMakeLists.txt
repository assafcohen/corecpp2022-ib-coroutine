cmake_minimum_required(VERSION 3.9)
project(CoreCPP2022_Coroutines CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

include(conan.cmake)

conan_cmake_configure(REQUIRES boost/1.79.0 fmt/9.0.0
        GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)


find_package(fmt)
find_package(boost)

add_subdirectory(SendFileCoroutine)
add_subdirectory(SendFileCallback)
add_subdirectory(SendFileBlocking)
add_subdirectory(emptyCoro)
add_subdirectory(emptyCoroLeak)
add_subdirectory(emptyCoroFixed)