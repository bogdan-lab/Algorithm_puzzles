#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <sstream>

using SetHolder = std::vector<std::set<int>>;


bool compare_two_sets(const std::set<int>& lhs, const std::set<int>& rhs){
    size_t dup_num = 0;
    for(const auto& el : lhs){
        dup_num += rhs.count(el);
        if(dup_num>=2) return true;
    }
    return false;
}

void process_set(std::istream& input=std::cin){
    size_t n;
    size_t k;
    int tmp;
    input >> n;
    SetHolder entire_set(n);
    for(size_t i=0; i<n; i++){
        input >> k;
        for(size_t j=0; j<k; j++){
            input >> tmp;
            entire_set[i].insert(tmp);
        }
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
