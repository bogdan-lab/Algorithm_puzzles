#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <stack>

static const std::unordered_map<char, char> EXPECTED{{'(', ')'}, {')', '('}};

void solve(std::istream& input=std::cin);
void process_requests(const std::string& brackets, const std::vector<size_t>& bnds);
size_t get_max_length(const std::string& brackets, const size_t start,
                      const size_t finish);



int main(){
    std::ios_base::sync_with_stdio (false);
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
    return 0;
}




void solve(std::istream &input){
    std::string brackets;
    input >> brackets;
    size_t m;
    input >> m;
    std::vector<size_t> bnds;
    bnds.reserve(m);
    std::copy_n(std::istream_iterator<size_t>(input), 2*m, std::back_inserter(bnds));
    std::for_each(bnds.begin(), bnds.end(), [](size_t& el){return el-1;});
    process_requests(brackets, bnds);
}


void process_requests(const std::string& brackets, const std::vector<size_t>& bnds){
    for(size_t i=0; i<bnds.size()/2; i++){
        std::cout << get_max_length(brackets, bnds[2*i], bnds[2*i+1]) << '\n';
    }
}

size_t get_max_length(const std::string &brackets, const size_t start,
                      const size_t finish){
    if(finish-start==0) return 0;
    size_t max_len = 0;
    std::stack<char> buff;
    buff.push(brackets[start]);
    size_t curr_size = 0;
    for(size_t i=start+1; i<finish+1; i++){
        if(!buff.empty() && brackets[i]==EXPECTED.at(buff.top())){
            curr_size++;
            max_len = std::max(max_len, curr_size);
            buff.pop();
        }
        else{
            curr_size = 0;
            buff.push(brackets[i]);
        }
    }
    return max_len;
}
