cmake_minimum_required(VERSION 3.26)
project(new_server_util)

set(CMAKE_CXX_STANDARD 17)

add_executable(new_server_util
    main.cpp
    include/Runnable.hpp
    include/util.h
    src/util.cpp
    include/pdmCli.h
    include/Runnable.hpp
    src/pdmCli.cpp)

target_include_directories(
    new_server_util
    PUBLIC
    include
)