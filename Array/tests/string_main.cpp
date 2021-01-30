#include "my_array.hpp"
#include "string_tests.hpp"
#include <string>
#include <algorithm>

int main(){
    CArray<std::string> test_array;
    //insert 15 random words
    push_random_str_group(test_array, 15u, 5, 42u);
    std::cout << test_array;
    //sort in increasing order
    std::sort(test_array.begin(), test_array.end());
    std::cout << test_array;
    //delete words with a, b,c,d,e
    char bad_symbols[] = {'a', 'b', 'c', 'd', 'e'};
    erase_with_bad_symbols(test_array, bad_symbols);
    std::cout << test_array;
    //insert 3 new words in random pos
    CArray<std::string> input;
    push_random_str_group(input, 3u, 7, 31u);
    mix_two_arrays(test_array, input, 27u);
    std::cout << test_array;
    return 0;
}

