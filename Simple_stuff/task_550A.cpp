#include <iostream>
#include <string>
#include <algorithm>


bool find_next_reversed_pair(const std::string& input, const std::string& sub){
    size_t start = input.find(sub);
    if(start == std::string::npos){
        return false;
    }
    std::string rev(sub);
    std::reverse(rev.begin(), rev.end());
    size_t rev_start = input.find(rev, std::min(start+sub.size(), input.size()-1));
    if(rev_start==std::string::npos){
        return false;
    }
    return true;
}


int main(){
    std::string input;
    std::cin >> input;
    if(input.size()<4){
        std::cout << "NO\n";
        return 0;
    }
    if(find_next_reversed_pair(input, "AB") || find_next_reversed_pair(input, "BA")){
        std::cout << "YES\n";
        return 0;
    }
    std::cout << "NO\n";
    return 0;
}
