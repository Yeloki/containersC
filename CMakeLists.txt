cmake_minimum_required(VERSION 3.22)
project(containers C)

set(CMAKE_C_STANDARD 17)

set(SRC_FILES array/array.c array/array.h)
set(SRC_FILES ${SRC_FILES} exception.c exception.h)

add_executable(containers main.c ${SRC_FILES})
