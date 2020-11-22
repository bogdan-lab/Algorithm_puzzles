#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

static size_t partition_call_count = 0;

size_t partition(std::vector<int>& vec, size_t from, size_t to){
    partition_call_count++;
    //srand(static_cast<uint>(time(0)));
    size_t left_idx = from;
    size_t el_idx = to-1;
    size_t rnd_idx = from + static_cast<size_t>(rand())%(to-from);
    std::swap(vec[el_idx], vec[rnd_idx]);
    size_t right_idx = to-1;
    while(true){
        while(vec[left_idx]<vec[el_idx]){ left_idx++;}
        while(vec[right_idx]>=vec[el_idx] && right_idx>from){right_idx--;}
        if(left_idx>=right_idx){
            std::swap(vec[el_idx], vec[left_idx]);
            break;
        }
        std::swap(vec[left_idx], vec[right_idx]);
        left_idx++;
        right_idx--;
    }
    return left_idx;
}

void k_order_sort(std::vector<int>& vec, size_t from, size_t to, size_t k){
    if(from>=to){ return;}
    size_t mid_pt = partition(vec, from, to);
    if(mid_pt-from>k){k_order_sort(vec, from, mid_pt, k);}
    if(to-mid_pt-1>k){k_order_sort(vec, mid_pt+1, to, k);}
}

std::vector<int> partial_sums(const std::vector<int>& src, size_t order){
    if(order>=src.size() || order == 0){return {};}
    std::vector<int> res;
    res.reserve(src.size()-order+1);
    int sum = std::accumulate(src.begin(),
                              src.begin()+static_cast<int>(order), 0);
    res.push_back(sum);
    for(size_t i=0; i<src.size()-order; i++){
        sum += src[i+order] - src[i];
        res.push_back(sum);
    }
    return res;
}


bool operator==(const std::vector<int>& lhs, const std::vector<int>& rhs){
    if(lhs.size()!=rhs.size()){return false;}
    for(size_t i=0; i<lhs.size(); i++){
        if(lhs[i]!=rhs[i]){return false;}
    }
    return true;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec){
    for(const auto& el : vec){
        out << el << " ; ";
    }
    return out << '\n';
}

TEST_CASE("partial sum test", ""){
    std::vector<int> tst = {1,2,3,4,5,6,7,8,9};
    std::vector<int> exp_1 = {1,2,3,4,5,6,7,8,9};
    std::vector<int> exp_2 = {3, 5, 7, 9, 11, 13, 15, 17};
    std::vector<int> exp_8 = {36, 44};
    CHECK(exp_1 == partial_sums(tst, 1));
    CHECK(exp_2 == partial_sums(tst, 2));
    CHECK(exp_8 == partial_sums(tst, 8));
}

TEST_CASE("k order sorting", ""){
    std::vector<int> tst = {3,4,6,32,79,2,4,9,3,76,234,8,0,-1,15};
    for(size_t i=tst.size()-1; i>0; i--){
        k_order_sort(tst, 0, tst.size(), i);
        std::vector<int> pt_sum = partial_sums(tst, i);
        CHECK(std::is_sorted(pt_sum.begin(), pt_sum.end()));
    }
    CHECK(std::is_sorted(tst.begin(), tst.end()));
}

TEST_CASE("Look at counter", ""){
    size_t N = 20;
    size_t size = 500;
    srand(static_cast<uint>(time(0)));
    std::vector<size_t> partition_calls;
    partition_calls.reserve(N);
    for(size_t n=0; n<N; n++){
        partition_call_count = 0;
        std::vector<int> tst;
        tst.reserve(size);
        for(size_t i=0; i<size; i++){
            tst.push_back(rand());
        }
        std::sort(tst.begin(), tst.end());
        k_order_sort(tst, 0, tst.size(), 1);
        CHECK(std::is_sorted(tst.begin(), tst.end()));
        partition_calls.push_back(partition_call_count);
    }
    std::cout << partition_calls;
    std::cout << "AVERAGE = "
              << std::accumulate(partition_calls.begin(), partition_calls.end(), 0u)/N
              << '\n';
}
