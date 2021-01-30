cmake_minimum_required(VERSION 3.10)

project(Array
	LANGUAGES CXX)


add_library(full_set_of_warnings INTERFACE)
include(../cmake/CompilerWarnings.cmake)
set_project_warnings(full_set_of_warnings)

add_library(my_array INTERFACE)
target_include_directories(my_array INTERFACE include)

#add_subdirectory(src)
add_subdirectory(tests)




