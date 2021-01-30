#include "my_array.hpp"
#include "string_tests.hpp"

#include <random>
#include <string>
#include <algorithm>

char get_random_char(std::mt19937& _rnd){
    unsigned l_bnd = static_cast<unsigned>('a');
    unsigned r_bnd = static_cast<unsigned>('z');
    std::uniform_int_distribution<unsigned> dist (l_bnd, r_bnd);
    return static_cast<char>(dist(_rnd));
}


std::string generate_random_word(std::mt19937& _rnd, const unsigned max_size){
    std::uniform_int_distribution<unsigned> dist(1, max_size);
    unsigned size = dist(_rnd);
    std::string word;
    word.reserve(size);
    while(size--){
        word+= get_random_char(_rnd);
    }
    return word;
}


void push_random_str_group(CArray<std::string>& _arr, unsigned _num,
                           const unsigned _max_word_size, const unsigned _seed){
    if(_num==0) return;
    std::mt19937 rnd(_seed);
    while(_num--){
        _arr.push_back(generate_random_word(rnd, _max_word_size));
    }
}


void erase_with_bad_symbols(CArray<std::string>& _arr, const char* bad_symbols){
    auto filter = [&](const std::string& word){
        unsigned size = sizeof(bad_symbols)/sizeof(bad_symbols[0]);
        for(unsigned i=0; i<size; i++){
            if(word.find(bad_symbols[i])!=std::string::npos){
                return true;
            }
        }
        return false;
    };
    unsigned idx = 0;
    while(idx<_arr.size()){
        if(filter(_arr[idx])){
            _arr.erase(idx);
            continue;
        }
        idx++;
    }
}

