cmake_minimum_required(VERSION 3.21)
project(cdns C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

add_executable(cdns
        main.c
        header.c header.h
        question.c question.h
        message.c message.h
        resource_record.c resource_record.h
        resource_records/a.h)

