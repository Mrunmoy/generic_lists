cmake_minimum_required(VERSION 3.9)
project(listtest C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)
add_executable(listtest main.c src/lists.c inc/lists.h src/list_intf.c inc/list_intf.h)
