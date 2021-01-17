#include <algorithm>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <vector>
#include <iterator>
#include <numeric>

size_t solve(std::istream& input = std::cin);
void run_tests();
size_t extract_points_with_min_loss(std::vector<size_t>& points, size_t& zero_counter);

int main(){
    run_tests();
    //std::cout << solve();
    return 0;
}


void run_tests(){
    /*{
        std::stringstream ss;
        ss << R"(2
              1 2)";
        size_t answer = solve(ss);
        assert(answer == 2);
    }
    {
        std::stringstream ss;
        ss << R"(3
              1 2 3)";
        size_t answer = solve(ss);
        assert(answer == 4);
    }
    {
        std::stringstream ss;
        ss << R"(9
             1 2 1 3 2 2 2 2 3)";
        size_t answer = solve(ss);
        assert(answer == 10);
    }*/
    {
        std::stringstream ss;
        ss << R"(100
              6 6 8 9 7 9 6 9 5 7 7 4 5 3 9 1 10 3 4 5 8 9 6 5 6 4 10 9 1 4 1 7 1 4 9 10 8 2 9 9 10 5 8 9 5 6 8 7 2 8 7 6 2 6 10 8 6 2 5 5 3 2 8 8 5 3 6 2 1 4 7 2 7 3 7 4 10 10 7 5 4 7 5 10 7 1 1 10 7 7 7 2 3 4 2 8 4 7 4 4)";
        size_t answer = solve(ss);
        assert(answer == 296); //296
    }
}

size_t solve(std::istream &input){
    size_t n;
    input >> n;
    std::vector<size_t> data;
    data.reserve(n);
    std::copy_n(std::istream_iterator<size_t>(input), n, std::back_inserter(data));
    size_t max_val = *(std::max_element(data.cbegin(), data.cend()));
    std::vector<size_t> points(max_val+1, 0);
    for(const auto el : data){
        points[el]+=el;
    }
    size_t zero_counter = static_cast<size_t>(std::count(points.begin(), points.end(), 0));
    size_t max_pts = 0;
    while(zero_counter<points.size()){
        max_pts += extract_points_with_min_loss(points, zero_counter);
    }
    return max_pts;
}

size_t extract_points_with_min_loss(std::vector<size_t>& points, size_t& zero_counter){
    size_t min_loss = std::numeric_limits<size_t>::max();
    size_t opt_pts_idx = 0;
    for(size_t i=0; i<points.size(); i++){
        if(points[i]!=0){
            size_t lhs_loss = i==0 ? 0 : points[i-1];
            size_t rhs_loss = i==points.size()-1 ? 0 : points[i+1];
            size_t curr_loss = lhs_loss + rhs_loss;
            if(min_loss>curr_loss){
                opt_pts_idx = i;
                min_loss = curr_loss;
            }
        }
    }
    size_t tmp = points[opt_pts_idx];
    points[opt_pts_idx] = 0;
    zero_counter++;
    if(opt_pts_idx>=1){
        zero_counter +=  points[opt_pts_idx-1]!=0;
        points[opt_pts_idx-1] = 0;
    }
    if(opt_pts_idx<points.size()-1){
        zero_counter += points[opt_pts_idx+1]!=0;
        points[opt_pts_idx+1] = 0;
    }
    return tmp;
}

