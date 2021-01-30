add_executable(int_tests int_tests.cpp int_main.cpp)
target_link_libraries(int_tests PRIVATE my_array)
add_executable(string_tests string_tests.cpp string_main.cpp)
target_link_libraries(string_tests PRIVATE my_array)
