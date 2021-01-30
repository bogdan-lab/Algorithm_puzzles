#ifndef STRING_TESTS_HPP
#define STRING_TESTS_HPP
#include <string>
#include <random>
#include"my_array.hpp"

char get_random_char(std::mt19937& _rnd);
std::string generate_random_word(std::mt19937& _rnd, const unsigned max_size);
void push_random_str_group(CArray<std::string>& _arr, unsigned _num,
                           const unsigned _max_word_size, const unsigned _seed);

void erase_with_bad_symbols(CArray<std::string>& _arr, const char* bad_symbols);


template <typename T>
void mix_two_arrays(CArray<T>& _target, const CArray<T>& _source, const unsigned _seed){
    std::mt19937 rnd(_seed);
    std::uniform_int_distribution<unsigned> dist(0, _target.size()-1);
    for(const auto& el : _source){
        _target.insert(dist(rnd), el);
    }
}



#endif //STRING_TESTS_HPP
