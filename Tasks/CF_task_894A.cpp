#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<size_t> find_all(const std::string& str, const char c){
    std::vector<size_t> vec;
    vec.reserve(str.size());
    for(size_t i=0; i<str.size(); i++){
        if (str[i]==c) vec.push_back(i);
    }
    return vec;
}

int main(){
    std::string input;
    input.reserve(100);
    std::cin >> input;
    std::vector<size_t> pos_a = find_all(input, 'A');
    std::vector<size_t> pos_q = find_all(input, 'Q');
    size_t num = 0;
    for(size_t i=0; i<pos_q.size(); i++){
        size_t q_start = pos_q[i];
        auto it = std::lower_bound(pos_a.cbegin(), pos_a.cend(), q_start);
        while(it!=pos_a.end()){
            size_t a_start = *it;
            num += pos_q.cend() - std::lower_bound(pos_q.cbegin(), pos_q.cend(), a_start);
            it++;
        }
    }
    std::cout << num << '\n';
    return 0;
}
