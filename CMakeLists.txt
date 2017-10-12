cmake_minimum_required (VERSION 3.7)
project (imgsketch)

set(CMAKE_C_FLAGS_DEBUG -ggdb)

set(INCLUDE_DIR ${CMAKE_BINARY_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

set(PROGRAM_NAME ${PROJECT_NAME})
set(PROGRAM_MAJOR_VERSION 0)
set(PROGRAM_MINOR_VERSION 1)
set(PROGRAM_PATCH_VERSION 1)
#configure_file(include/config.h.in ${INCLUDE_DIR}/config.h)

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.c lib/bar.c)
include_directories(${INCLUDE_DIR} include lib)
include(tests/CMakeLists.txt)
	
add_executable(${PROJECT_NAME} ${SRC_FILES} imgsketch.c)

target_link_libraries(${PROJECT_NAME} png m)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
