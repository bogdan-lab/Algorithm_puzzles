#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>

using SetHolder = std::vector<std::vector<int>>;


bool compare_two_sets(const std::vector<int>& lhs, const std::vector<int>& rhs){
    if(lhs.size()<=1 || rhs.size()<=1) return false;
    auto lhs_start_it = std::lower_bound(lhs.cbegin(), lhs.cend(), rhs.front());
    auto lhs_end_it = std::upper_bound(lhs.cbegin(), lhs.cend(), rhs.back());
    auto rhs_start_it = std::lower_bound(rhs.cbegin(), rhs.cend(), lhs.front());
    auto rhs_end_it = std::upper_bound(rhs.cbegin(), rhs.cend(), lhs.back());
    size_t dup_num = 0;
    for(auto it = lhs_start_it; it!=lhs_end_it; it++){
        dup_num += std::binary_search(rhs_start_it, rhs_end_it, *it);
        if(dup_num>=2) return true;
    }
    return false;
}

void process_set(std::istream& input=std::cin){
    size_t n;
    size_t k;
    input >> n;
    SetHolder entire_set(n);
    for(size_t i=0; i<n; i++){
        input >> k;
        entire_set[i].reserve(k);
        std::copy_n(std::istream_iterator<int>(input), k, std::back_inserter(entire_set[i]));
        auto new_end = std::unique(entire_set[i].begin(), entire_set[i].end());
        for(int idx=0; idx<new_end-entire_set[i].end(); idx++) entire_set[i].pop_back();
        std::sort(entire_set[i].begin(), entire_set[i].end());
    }
    //Check for pair
    for(size_t i=0; i<n; i++){
        for(size_t j=i+1; j<n; j++){
            if(compare_two_sets(entire_set[i], entire_set[j])){
                std::cout << i+1 << " " << j+1 << '\n';
                return;
            }
        }
    }
    std::cout << -1 << '\n';
}

void solve(std::istream& input=std::cin){
    size_t t;
    input >> t;
    for(size_t i=0; i<t; i++){
        process_set(input);
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
    solve();
    return 0;
}
