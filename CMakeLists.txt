cmake_minimum_required(VERSION 3.22.1)
project(catnet)

set(CMAKE_CXX_STANDARD 17)

add_executable(catnet src/main.cpp
        src/log/log.h
        src/log/log.cpp
)
