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
find_package(Qt5Charts)

include_directories(include)

set(pipid_src
    src/pid_controller.cpp
    src/gui.cpp
    src/encoder_counter.cpp
    src/motor_driver.cpp
    src/pid_controller.cpp
    src/delegate_logger.cpp
# AUTOMOC does not process headers automatically, add them manually
    include/gui.h
    include/delegate_logger.h
)

add_library(pipid STATIC ${pipid_src})
target_link_libraries(pipid Qt5::Core Qt5::Widgets Qt5::Charts wiringPi)

###########################################################

if(UNIT_TEST)
    # Gui test
    add_executable(gui_test test/gui_test.cpp)
    target_link_libraries(gui_test pipid pthread)
    
    # Incremental encoder class test
    add_executable(incremental_encoder 
                   test/incremental_encoder.cpp
                   src/encoder_counter.cpp)
    target_compile_definitions(incremental_encoder PUBLIC PRINT_ENCODER)
    target_link_libraries(incremental_encoder wiringPi)

    # PWM unit test (motor driver)
    add_executable(pwm_driver 
                   test/pwm_driver.cpp
                   src/motor_driver.cpp)
    target_link_libraries(pwm_driver wiringPi)

    # Basic PID test w/ encoder & motor driver 
    add_executable(simple_pid
                   test/simple_pid.cpp)
    target_link_libraries(simple_pid -lpthread wiringPi pipid)
endif()

if(BUILD_TOOLS)
endif()
