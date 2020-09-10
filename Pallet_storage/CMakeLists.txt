cmake_minimum_required(VERSION 3.10)

project(PalletStorage
	LANGUAGES CXX)

add_compile_options(-g -O0 -std=c++17)
add_executable(solution
		solution.cpp)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_library(full_set_of_warnings INTERFACE)

include(../cmake/CompilerWarnings.cmake)
set_project_warnings(full_set_of_warnings)

target_link_libraries(solution PRIVATE full_set_of_warnings)

