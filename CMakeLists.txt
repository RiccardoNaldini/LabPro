cmake_minimum_required(VERSION 3.27)
project(LabPro)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(LabPro main.cpp
        Date.cpp
        Date.h
        Activity.h
        Record.cpp
        Record.h)

target_link_libraries(untitled ${CURSES_LIBRARIES})