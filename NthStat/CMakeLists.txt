cmake_minimum_required(VERSION 3.10)

project(NthStat
	LANGUAGES CXX)

add_executable(solution
		solution.cpp)

set_target_properties(solution PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON)

add_library(full_set_of_warnings INTERFACE)
include(../cmake/CompilerWarnings.cmake)
set_project_warnings(full_set_of_warnings)

#CONAN
find_program(CONAN conan)
if (NOT CONAN)
    message(FATAL_ERROR "Needs conan package manager: please visit https://conan.io and install")
endif ()
include(../cmake/conan.cmake)
conan_check(VERSION 1.14.4 REQUIRED)
conan_cmake_run(REQUIRES
                catch2/2.13.3
        OPTIONS BASIC_SETUP CMAKE_TARGETS
        BUILD missing)


target_link_libraries(solution PRIVATE full_set_of_warnings CONAN_PKG::catch2)

