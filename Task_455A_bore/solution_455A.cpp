#include <algorithm>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <vector>
#include <iterator>
#include <numeric>


int64_t solve(std::istream& input = std::cin);
void run_tests();

int main(){
    //run_tests();
    std::cout << solve();
    return 0;
}


void run_tests(){
    {
        std::stringstream ss;
        ss << R"(2
              1 2)";
        int64_t answer = solve(ss);
        assert(answer == 2);
    }
    {
        std::stringstream ss;
        ss << R"(3
              1 2 3)";
        int64_t answer = solve(ss);
        assert(answer == 4);
    }
    {
        std::stringstream ss;
        ss << R"(9
             1 2 1 3 2 2 2 2 3)";
        int64_t answer = solve(ss);
        assert(answer == 10);
    }
    {
        std::stringstream ss;
        ss << R"(100
              6 6 8 9 7 9 6 9 5 7 7 4 5 3 9 1 10 3 4 5 8 9 6 5 6 4 10 9 1 4 1 7 1 4 9 10 8 2 9 9 10 5 8 9 5 6 8 7 2 8 7 6 2 6 10 8 6 2 5 5 3 2 8 8 5 3 6 2 1 4 7 2 7 3 7 4 10 10 7 5 4 7 5 10 7 1 1 10 7 7 7 2 3 4 2 8 4 7 4 4)";
        int64_t answer = solve(ss);
        assert(answer == 296);
    }
    {
        std::stringstream ss;
        ss << 100'000 << '\n';
        for(int64_t i=0; i<100'000; i++) ss << 100'000 << ' ';
        int64_t answer = solve(ss);
        assert(answer == 10'000'000'000);
    }
}

int64_t solve(std::istream &input){
    size_t n;
    input >> n;
    std::vector<size_t> data;
    data.reserve(n);
    std::copy_n(std::istream_iterator<size_t>(input), n, std::back_inserter(data));
    size_t max_val = *(std::max_element(data.cbegin(), data.cend()));
    std::vector<int64_t> points(max_val+1, 0);
    for(const auto el : data){
        points[el]+=static_cast<int64_t>(el);
    }
    for(size_t i=2; i<points.size(); i++){
        points[i] = std::max(points[i-1], points[i-2]+points[i]);
    }
    return points.back();
}
