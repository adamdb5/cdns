cmake_minimum_required(VERSION 3.20)
project(cdns C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

include_directories(include)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)