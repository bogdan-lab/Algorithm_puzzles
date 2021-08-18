cmake_minimum_required(VERSION 3.10)

project(MergeInversionCounter
	LANGUAGES CXX)

add_library(full_set_warnings INTERFACE)
set(WARNINGS_AS_ERRORS FALSE)
include(../cmake/CompilerWarnings.cmake)
set_project_warnings(full_set_warnings)


add_executable(solution
		solution.cpp)

add_compile_options(-g -O0 -std=c++17)

target_link_libraries(solution PRIVATE full_set_warnings)
target_include_directories(solution PRIVATE /home/bogdan/workplace/Bibliotech/libs/boost_1_74_0/)
