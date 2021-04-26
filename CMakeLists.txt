cmake_minimum_required(VERSION 3.16)
project(StardustEmu CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(StardustEmu main.cpp include/memory.cpp include/memory.h)