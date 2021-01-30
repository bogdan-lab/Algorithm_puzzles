#include "int_tests.hpp"
#include "my_array.hpp"
#include<random>
#include<algorithm>


void push_random_group(
  CArray<int>& _arr,
  unsigned _num,
  const int _l_bnd,
  const int _r_bnd,
  unsigned _seed
)
{
  std::mt19937 rnd(_seed);
  std::uniform_int_distribution<int> dist(_l_bnd, _r_bnd);
  while(_num--){
      int tmp = dist(rnd);
    _arr.push_back(tmp);
  }
}

void erase_every(CArray<int>& _arr, const unsigned _gap){
    if(_gap>_arr.size()) return;
    if(_gap==0) return;
    if(_gap==1){
        _arr.clear();
        return;
    }
    unsigned cur_pos = 0;
    unsigned next = _gap-1;
    while(cur_pos+next<_arr.size()){
        _arr.erase(cur_pos+next);
        cur_pos+=next;
    }
}

void insert_random_places(CArray<int>& _target, const CArray<int>& _source, const unsigned _seed){
    std::mt19937 rnd(_seed);
    std::uniform_int_distribution<unsigned> dist(0, _target.size()-1);
    for(const int el : _source){
        _target.insert(dist(rnd), el);
    }
}

