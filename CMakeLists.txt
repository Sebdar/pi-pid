# PiPid CMake config

cmake_minimum_required(VERSION 3.1.0)

project(pipid-lib CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

###########################################################

option(UNIT_TEST "Build unit tests" OFF)
option(BUILD_TOOLS "Build tools" OFF)

###########################################################

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(include)

set(pipid_src src/controller.cpp)

add_library(pipid STATIC ${pipid_src})
target_link_libraries(pipid Qt5::Core Qt5::Widgets)

###########################################################

if(UNIT_TEST)

endif()

if(BUILD_TOOLS)

endif()
