cmake_minimum_required(VERSION 3.21)
project(cdns C)

set(CMAKE_C_STANDARD 99)

add_executable(cdns main.c header.h header.c question.c question.h message.c message.h)
