cmake_minimum_required(VERSION 3.16)
project(raylib_project)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)

add_executable(game src/main.cpp)

target_link_libraries(game raylib)
