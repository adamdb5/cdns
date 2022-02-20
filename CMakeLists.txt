cmake_minimum_required(VERSION 3.21)
project(cdns C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)