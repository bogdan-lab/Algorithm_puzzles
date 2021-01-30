#ifndef INT_TESTS_HPP
#define INT_TESTS_HPP

#include "my_array.hpp"

void push_random_group(
  CArray<int>& _arr,
  unsigned _num,
  const int _l_bnd,
  const int _r_bnd,
  unsigned seed
);

void quick_sort(CArray<int>& _arr, const unsigned _from, const unsigned _to);
void partition(CArray<int>& _arr, const unsigned _from, const unsigned _to);
void erase_every(CArray<int>& _arr, const unsigned _gap);
void insert_random_places(CArray<int>& _target, const CArray<int>& _source, const unsigned _seed);



#endif //INT_TESTS_HPP
