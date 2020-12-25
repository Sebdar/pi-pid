# PiPid CMake config

cmake_minimum_required(VERSION 3.0)

project(pipid-lib)
include_directories(include)

set(pipid_src src/controller.cpp)

add_library(pipid-lib STATIC ${pipid_src})
