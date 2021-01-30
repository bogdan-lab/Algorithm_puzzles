#include "my_array.hpp"
#include "int_tests.hpp"

#include <algorithm>








int main()
{
  //fill 20 random 0 - 100
  CArray<int> test_arr;
  push_random_group(test_arr, 20u, 0, 100, 42u);
  std::cout << test_arr;
  //sort CArray
  std::sort(test_arr.begin(), test_arr.end());
  //quick_sort(test_arr, 0, test_arr.size());
  std::cout << test_arr;
  //erase every 2 element
  erase_every(test_arr, 2);
  std::cout << test_arr;
  //insert 10 random 1-100 in random pos
  CArray<int> input;
  push_random_group(input, 10u, 0, 100, 29u);
  insert_random_places(test_arr, input, 37u);
  //clear
  test_arr.clear();
  std::cout << test_arr;
  return 0;
}
