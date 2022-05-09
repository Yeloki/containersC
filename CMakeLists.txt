cmake_minimum_required(VERSION 3.22)
project(containers C)

set(CMAKE_C_STANDARD 17)

set(SRC_FILES array/array.c array/array.h array/tools.h)
set(SRC_FILES ${SRC_FILES} queue/queue.c queue/queue.h)
set(SRC_FILES ${SRC_FILES} stack/stack.c stack/stack.h)
set(SRC_FILES ${SRC_FILES} exception/exception.c exception/exception.h exception/exceptions_list.h)

add_executable(containers main.c ${SRC_FILES})
