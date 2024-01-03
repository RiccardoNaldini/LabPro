cmake_minimum_required(VERSION 3.27)
project(LabPro)

set(CMAKE_CXX_STANDARD 17)

add_executable(LabPro main.cpp
        Date.cpp
        Date.h
        Activity.h
        Record.cpp
        Record.h)
