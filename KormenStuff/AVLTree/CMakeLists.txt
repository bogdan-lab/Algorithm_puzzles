cmake_minimum_required(VERSION 3.10)

project(AVLTree
	LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)


add_executable(app
		main.cpp)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_library(full_set_of_warnings INTERFACE)

include(../cmake/CompilerWarnings.cmake)
set_project_warnings(full_set_of_warnings)

set(GTEST_PATH ../../third_party/googletest)
add_subdirectory(${GTEST_PATH} ${GTEST_PATH}/build)


target_include_directories(app PRIVATE ${GTEST_PATH}/googletest ${GTEST_PATH}/googlemock)
target_link_libraries(app PRIVATE full_set_of_warnings gtest)
