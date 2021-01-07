#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_set>
#include <random>
#include <time.h>
#include <utility>

using ElCollection = std::unordered_set<int>;
using SetHolder = std::vector<ElCollection>;

bool compare_two_sets(const ElCollection& lhs, const ElCollection& rhs){
    size_t dup_num = 0;
    for(const auto& el : lhs){
        dup_num += rhs.count(el);
        if(dup_num>=2) return true;
    }
    return false;
}


void fill_minmax_stat(std::vector<int>& min_el, std::vector<int>& max_el,
                      const SetHolder& entire_set){
    for(size_t i=0; i<entire_set.size(); i++){
        auto it = std::minmax_element(entire_set[i].begin(), entire_set[i].end());
        min_el[i] = *(it.first);
        max_el[i] = *(it.second);
    }
}

void process_set(std::mt19937& rnd, std::istream& input=std::cin){
    size_t n;
    size_t k;
    input >> n;
    SetHolder entire_set(n);
    for(size_t i=0; i<n; i++){ 	 	//O(n)
        input >> k;
        entire_set[i].max_load_factor(1.0);
        entire_set[i].reserve(k);
        std::copy_n(std::istream_iterator<int>(input), k,
                    std::insert_iterator<ElCollection>(entire_set[i], entire_set[i].end()));
    }
    std::vector<int> minimum_el_in_set(n);
    std::vector<int> maximum_el_in_set(n);
    fill_minmax_stat(minimum_el_in_set, maximum_el_in_set, entire_set); 	//O(n)
    //For better average performance
    std::vector<size_t> idxes(n);
    std::iota(idxes.begin(), idxes.end(), 0);
    std::shuffle(idxes.begin(), idxes.end(), rnd); 	 	 	//O(n)
    //Check for pair
    for(size_t i=0; i<n; i++){
        size_t lhs_idx = idxes[i];
        for(size_t j=i+1; j<n; j++){
            size_t rhs_idx = idxes[j];
            if(maximum_el_in_set[lhs_idx]>minimum_el_in_set[rhs_idx]
               && maximum_el_in_set[rhs_idx]>minimum_el_in_set[lhs_idx]
               && compare_two_sets(entire_set[lhs_idx], entire_set[rhs_idx])){
                std::cout << lhs_idx+1 << " " << rhs_idx+1 << '\n';
                return;
            }
        }
    }
    std::cout << -1 << '\n';
}

void solve(std::mt19937& rnd, std::istream& input=std::cin){
    size_t t;
    input >> t;
    for(size_t i=0; i<t; i++){
        process_set(rnd, input);
    }
}

int main(){
    std::ios_base::sync_with_stdio (false);
    std::stringstream ss;
    ss << R"(3
          4
          2 1 10
          3 1 3 5
          5 5 4 3 2 1
          3 10 20 30
          3
          4 1 2 3 4
          4 2 3 4 5
          4 3 4 5 6
          2
          3 1 3 5
          3 4 3 2)";
    std::mt19937 rnd(static_cast<unsigned int>(time(NULL)));
    solve(rnd);
    return 0;
}
