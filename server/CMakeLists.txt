cmake_minimum_required(VERSION 3.17)
project(server)

set(CMAKE_CXX_STANDARD 14)


find_package(Threads)

include_directories("include")

add_executable(server main.cpp include/server-loop.h)

target_link_libraries (server ${CMAKE_THREAD_LIBS_INIT})

