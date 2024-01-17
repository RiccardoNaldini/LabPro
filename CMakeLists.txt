cmake_minimum_required(VERSION 3.27)
project(LabPro)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(test)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE_FILES
        Date.cpp
        Date.h
        Activity.h
        Record.cpp
        Record.h
)


add_executable(LabPro main.cpp ${SOURCE_FILES})
add_library(core ${SOURCE_FILES})
target_link_libraries(LabPro ${CURSES_LIBRARIES} core)

