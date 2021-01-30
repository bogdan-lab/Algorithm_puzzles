#include "int_tests.hpp"
#include "my_array.hpp"
#include<random>
#include<algorithm>


void push_random_group(
  CArray<int>& _arr,
  unsigned _num,
  const int _l_bnd,
  const int _r_bnd,
  const unsigned _seed
)
{
  std::mt19937 rnd(_seed);
  std::uniform_int_distribution<> dist(_l_bnd, _r_bnd);
  while(_num--){
    _arr.push_back(dist(rnd));
  }
}


void partition(CArray<int>& _arr, const unsigned _from, const unsigned _to){
    unsigned left_idx = _from;
    unsigned el_idx = _to-1;
    unsigned right_idx = _to-1;
    while(true){
        while(left_idx<_arr.size() && _arr[left_idx]<_arr[el_idx]){
            left_idx++;
        }
        while(righ_idx>_from && _arr[right_idx]>=_arr[el_idx]){
            right_idx--;
        }
        if(left_idx>=right_idx){
            std::swap(_arr[el_idx], _arr[left_idx]);
            break;
        }
        std::swap(_arr[left_idx], _arr[right_idx]);
        left_idx++;
        right_idx--;
    }
    return left_idx;
}

void quick_sort(CArray<int>& _arr, const unsigned _from, const unsigned _to){
  if(_to==0 || _from>=_to-1) return;
  unsigned mid = partition(_arr, _from, _to);
  quick_sort(_arr, _from, mid);
  quick_sort(_arr, mid+1, _to);
}


void erase_every(CArray<int> _arr, const unsigned _gap){
    if(_gap>_arr.size()) return;
    for(unsigned i=gap-1; i<_arr.size(); i+=gap){
        _arr.erase(i);
    }
}

void insert_random_places(CArray& _target, const CArray& _source, const unsigned _seed){
    std::mt19937 rnd(_seed);
    std::uniform_int_distribution<unsigned> dist(0, _target.size()-1);
    for(unsigned i=0; i<_source.size(); i++){
        _target.insert(dist(rnd), _source[i]);
    }
}

