file(GLOB TESTS "tests/*.c")

foreach(FILE ${TESTS})
    get_filename_component(FILE_NAME ${FILE} NAME_WE)
    string(TOUPPER ${FILE_NAME} TEST_NAME)
    add_executable(test_${FILE_NAME} ${SRC_FILES} ${FILE})
    add_test(NAME ${TEST_NAME}_TEST COMMAND test_${FILE_NAME})
    target_link_libraries(test_${FILE_NAME} png m)
endforeach()

