cmake_minimum_required(VERSION 3.15)

project(slimsim)

set(CMAKE_C_STANDARD 11)

find_package(raylib REQUIRED)

add_executable(ss main.c)

target_link_libraries(ss raylib)
