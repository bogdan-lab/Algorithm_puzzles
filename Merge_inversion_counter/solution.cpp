/*Задача - Найти количество инверсий в массиве за nlog(n).
 * Инверсия это когда i<j, но A[i]>A[j]                   */

#include <iostream>
#include <vector>
#include <assert.h>
#include <ctime>
#include "boost/random/mersenne_twister.hpp"
#include "boost/random/uniform_int_distribution.hpp"

void swap(int& lhs, int& rhs){
    int tmp = rhs;
    rhs = lhs;
    lhs = tmp;
}


size_t merge(std::vector<int>::iterator begin, std::vector<int>::iterator mid, std::vector<int>::iterator end){
    std::vector<int> lhs(begin, mid);
    std::vector<int> rhs(mid, end);
    size_t lhs_id = 0;
    size_t rhs_id = 0;
    size_t count = 0;
    for(int i=0; i<end-begin; i++){
        if(lhs_id>=lhs.size()){
            *(begin+i) = rhs[rhs_id];
            rhs_id++;
        }
        else if (rhs_id>=rhs.size()){
            *(begin+i) = lhs[lhs_id];
            lhs_id++;
        }
        else if(lhs[lhs_id]<=rhs[rhs_id]){
            *(begin+i) = lhs[lhs_id];
            lhs_id++;
        }
        else {
            *(begin+i) = rhs[rhs_id];
            rhs_id++;
            count += lhs.size() - lhs_id;
        }
    }
    return count;
}


size_t calculate_inversions(std::vector<int>::iterator begin, std::vector<int>::iterator end){
    if(end-begin<=1){
        return 0;
    }
    size_t count = 0;
    std::vector<int>::iterator mid = begin + (end-begin)/2;
    count += calculate_inversions(begin, mid);
    count += calculate_inversions(mid, end);
    count += merge(begin, mid, end);
    return count;
}


size_t brut_force_solution(const std::vector<int>& vec){
    if(vec.size()==0){return 0;}
    size_t count = 0;
    for(size_t i=0; i<vec.size()-1; i++){
        for(size_t j=i+1; j<vec.size(); j++){
            if(vec[i]>vec[j]){
                count++;
            }
        }
    }
    return count;
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec){
    if(vec.size()==0){
        out << "[]";
        return out;
    }
    out << "[ ";
    for(size_t i=0; i<vec.size()-1; i++){
        out << vec[i] << ", ";
    }
    out << vec[vec.size()-1] << " ]";
    return out;
}

int main(){
    {
        std::vector<int> test = {2,3,8,6,1};
        size_t res2 = brut_force_solution(test);
        size_t res1 = calculate_inversions(test.begin(), test.end());
        assert(res1==5);
        assert(res2==5);
    }
    {
        std::vector<int> test={5, 4, 3, 2, 1};
        size_t res2 = brut_force_solution(test);
        size_t res1 = calculate_inversions(test.begin(), test.end());
        assert(res1==10);
        assert(res2==10);
    }
    {
        std::vector<int> test={1,2,3,4,5};
        size_t res2 = brut_force_solution(test);
        size_t res1 = calculate_inversions(test.begin(), test.end());
        assert(res1==0);
        assert(res2==0);
    }
    boost::random::mt19937 gen(static_cast<uint>(std::time(0)));
    boost::random::uniform_int_distribution<> num_dist(-100, 100);
    boost::random::uniform_int_distribution<> len_dist(0, 20);
    std::vector<int> test_vec;
    for(size_t N=0; N<20; N++){
        size_t len = static_cast<size_t>(len_dist(gen));
        test_vec.reserve(len);
        for(size_t i=0; i<len; i++){
            test_vec.push_back(num_dist(gen));
        }
        std::cerr << "Testing vector: " << test_vec << "\n";
        size_t res1 = brut_force_solution(test_vec);
        size_t res2 = calculate_inversions(test_vec.begin(), test_vec.end());
        assert(res1==res2);
        std::cerr << "Counted " << res1 << " inversions\n";
        test_vec.clear();
    }
    return 0;
}
