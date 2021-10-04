cmake_minimum_required(VERSION 3.20)
project(Stack)

set(CMAKE_CXX_STANDARD 11)

add_executable(Stack main.cpp stack.cpp errorlib.cpp tests/test.h tests/test.cpp)
