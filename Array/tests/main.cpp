#include "my_array.hpp"
#include "tests.hpp"
#include <string>
#include <algorithm>


void run_int_tests();
void run_string_tests();


int main(){
  run_int_tests();
  run_string_tests();

  return 0;
}


void run_int_tests(){
  std::mt19937 rnd(42u);
  std::uniform_int_distribution<int> dist(0, 100);
  auto int_gen = [&](){
      return dist(rnd);
  };
  //fill 20 random 0 - 100
  CArray<int> test_arr;
  push_random_group(test_arr, 20u, int_gen);
  std::cout << test_arr;
  //sort CArray
  std::sort(test_arr.begin(), test_arr.end());
  std::cout << test_arr;
  //erase every 2 element
  erase_every(test_arr, 2);
  std::cout << test_arr;
  //insert 10 random 1-100 in random pos
  CArray<int> input;
  push_random_group(input, 10u, int_gen);
  mix_two_arrays(test_arr, input, rnd);
  std::cout << test_arr;
  //clear
  test_arr.clear();
  std::cout << test_arr;
}

void run_string_tests(){
  CArray<std::string> test_array;
  //insert 15 random words
  std::mt19937 rnd;
  unsigned max_word_size = 7u;
  auto word_gen = [&](){ return generate_random_word(rnd, max_word_size);};
  push_random_group(test_array, 15u, word_gen);
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
  push_random_group(input, 3u, word_gen);
  mix_two_arrays(test_array, input, rnd);
  std::cout << test_array;
}
