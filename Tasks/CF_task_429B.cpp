#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include<stdio.h>

using Collection = std::vector<unsigned>;
using CollectionD = std::vector<double>;

double get_min_d(Collection& pos, const unsigned st_end){
    auto unique_end = std::unique(pos.begin(), pos.end());
    std::sort(pos.begin(), unique_end);
    CollectionD possible_d;
    possible_d.reserve((unique_end-pos.begin()-1) + 2);
    possible_d.push_back(static_cast<double>(pos.front()));
    for(auto it=next(pos.begin()); it!=unique_end; it++){
        possible_d.push_back(static_cast<double>(*it-*prev(it))/2.0);
    }
    possible_d.push_back(static_cast<double>(st_end-*prev(unique_end)));
    auto res_it = std::max_element(possible_d.cbegin(), possible_d.cend());
    return *res_it;
}

int main(){
    unsigned n, l;
    std::cin >> n >> l;
    Collection pos;
    pos.reserve(n);
    std::copy_n(std::istream_iterator<unsigned>(std::cin), n, std::back_inserter(pos));
    double res = get_min_d(pos, l);
    printf("%.10lf\n", res);

    return 0;
}
