cmake_minimum_required(VERSION 3.10)

project(task_1468M
	LANGUAGES CXX)

add_executable(solution
		solution.cpp)

set_target_properties(solution PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON)

add_library(full_set_of_warnings INTERFACE)
include(../cmake/CompilerWarnings.cmake)
set_project_warnings(full_set_of_warnings)

target_link_libraries(solution PRIVATE full_set_of_warnings)

