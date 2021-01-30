#ifndef STRING_TESTS_HPP
#define STRING_TESTS_HPP
#include <string>
#include <random>
#include"my_array.hpp"

char get_random_char(
  std::mt19937& _rnd
);

std::string generate_random_word(
  std::mt19937& _rnd,
  const unsigned _max_size
);

void erase_with_bad_symbols(
  CArray<std::string>& _arr,
  const char* _bad_symbols
);

void erase_every(
  CArray<int>& _arr,
  const unsigned _gap
);


template <typename T, typename G>
void push_random_group(
  CArray<T>& _arr,
  unsigned _num,
  G _generator
)
{
  if(_num==0) return;
  while(_num--)
  {
    _arr.push_back(_generator());
  }
}


template <typename T>
void mix_two_arrays(
  CArray<T>& _target,
  const CArray<T>& _source,
  std::mt19937& _rnd
)
{
  std::uniform_int_distribution<unsigned> dist(0, _target.size()-1);
  for(const auto& el : _source)
  {
    _target.insert(dist(_rnd), el);
  }
}



#endif //STRING_TESTS_HPP
