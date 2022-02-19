cmake_minimum_required(VERSION 3.21)
project(cdns C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Choose what messages should be compiled into the library
list(   APPEND
        SUPPORTED_MESSAGE_TYPES
        "a"
        "aaaa"
)

add_executable(${PROJECT_NAME}
        main.c
        header.c header.h
        question.c question.h
        message.c message.h
        resource_record.c resource_record.h)

add_subdirectory(messages)

list(APPEND LINK_LIBS "")
FOREACH(MESSAGE_TYPE ${SUPPORTED_MESSAGE_TYPES})
    list(APPEND LINK_LIBS ${PROJECT_NAME}_${MESSAGE_TYPE})
ENDFOREACH()

target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})
