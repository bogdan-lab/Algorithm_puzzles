#include "my_array.hpp"
#include "tests.hpp"

#include <random>
#include <string>
#include <algorithm>

char get_random_char(
  std::mt19937& _rnd
)
{
  unsigned l_bnd = static_cast<unsigned>('a');
  unsigned r_bnd = static_cast<unsigned>('z');
  std::uniform_int_distribution<unsigned> dist (l_bnd, r_bnd);
  return static_cast<char>(dist(_rnd));
}


std::string generate_random_word(
  std::mt19937& _rnd,
  const unsigned max_size
)
{
  std::uniform_int_distribution<unsigned> dist(1, max_size);
  unsigned size = dist(_rnd);
  std::string word;
  word.reserve(size);
  while(size--){
    word+= get_random_char(_rnd);
  }
  return word;
}

void erase_with_bad_symbols(
  CArray<std::string>& _arr,
  const char* _bad_symbols
)
{
  auto filter = [&](const std::string& word){
    unsigned size = sizeof(_bad_symbols)/sizeof(_bad_symbols[0]);
    for(unsigned i=0; i<size; i++){
      if(word.find(_bad_symbols[i])!=std::string::npos)
      {
        return true;
      }
    }
    return false;
  };
  unsigned idx = 0;
  while(idx<_arr.size())
  {
    if(filter(_arr[idx]))
    {
      _arr.erase(idx);
      continue;
    }
    idx++;
  }
}

void erase_every(
  CArray<int>& _arr,
  const unsigned _gap
)
{
  if(_gap>_arr.size()) return;
  if(_gap==0) return;
  if(_gap==1)
  {
    _arr.clear();
    return;
  }
  unsigned cur_pos = 0;
  unsigned next = _gap-1;
  while(cur_pos+next<_arr.size())
  {
    _arr.erase(cur_pos+next);
    cur_pos+=next;
  }
}
