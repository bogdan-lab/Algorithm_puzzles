#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>

void solve(std::istream& input=std::cin);
void process_requests(const std::string& brackets, const std::vector<size_t>& bnds);
size_t get_max_length(const std::string& brackets, const size_t start,
                      const size_t finish);


void run_tests();
int main(){
    std::ios_base::sync_with_stdio (false);
    std::cin.tie(nullptr);
    solve(std::cin);
    return 0;
}




void solve(std::istream &input){
    std::string brackets;
    input >> brackets;
    size_t m;
    input >> m;
    std::vector<size_t> bnds;
    bnds.reserve(2*m);
    std::copy_n(std::istream_iterator<size_t>(input), 2*m, std::back_inserter(bnds));
    std::for_each(bnds.begin(), bnds.end(), [](size_t& el){el--;});
    process_requests(brackets, bnds);
}


void process_requests(const std::string& brackets, const std::vector<size_t>& bnds){
    for(size_t i=0; i<bnds.size()/2; i++){
        std::cout << get_max_length(brackets, bnds[2*i], bnds[2*i+1]) << '\n';
    }
}

size_t get_max_length(const std::string& brackets, const size_t start,
                      const size_t finish){
    if(finish<=start) return 0;
    size_t begin = brackets.find('(', start);
    if(begin==std::string::npos) return 0;
    size_t end = brackets.rfind(')', finish);
    if(end==std::string::npos || end<=begin) return 0;
    size_t count_right = 0;
    size_t count_left = 0;
    for(size_t i=begin; i<end+1; i++){
        count_right += brackets[i]=='(';
        count_left += brackets[i]==')' && count_right>count_left;
    }
    return 2*count_left;
}


void run_tests(){
    {
        std::stringstream ss;
        ss << "())(())(())(\n";
        ss << R"(7
              1 1
              2 3
              1 2
              1 12
              8 12
              5 11
              2 10)";
        solve(ss);
    }
    {
        std::stringstream ss;
        ss << "())(()\n";
        ss<<R"(1
            1 6)";
        solve(ss);
    }
}
