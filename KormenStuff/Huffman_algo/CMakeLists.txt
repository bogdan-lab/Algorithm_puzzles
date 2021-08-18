cmake_minimum_required(VERSION 3.10)

project(Huffman
	LANGUAGES CXX)

add_executable(encode
		encoder.cpp)

add_executable(decode
		decoder.cpp)

add_library(full_set_of_warnings INTERFACE)

include(../cmake/CompilerWarnings.cmake)
set_project_warnings(full_set_of_warnings)

target_link_libraries(encode PRIVATE full_set_of_warnings)
target_link_libraries(decode PRIVATE full_set_of_warnings)


