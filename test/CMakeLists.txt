file(GLOB TEST_FILES *.c)

find_package(CMOCKA REQUIRED)

foreach (TEST_FILE IN ITEMS ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE} test_message.c)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    target_include_directories(${TEST_NAME} PRIVATE ${CMOCKA_INCLUDE_DIR})
    target_link_libraries(${TEST_NAME} ${CMOCKA_LIBRARIES} ${PROJECT_NAME})
endforeach ()