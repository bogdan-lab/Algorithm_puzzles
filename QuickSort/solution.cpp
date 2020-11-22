#include <vector>
#include <algorithm>
#include <string>
//#include <time.h>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

template <typename T>
size_t partition(std::vector<T>& vec, size_t from, size_t to){
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

template <typename T>
void quick_sort(std::vector<T>& vec, size_t from, size_t to){
    if(from>=to){ return;}
    size_t mid_pt = partition(vec, from, to);
    quick_sort(vec, from, mid_pt);
    quick_sort(vec, mid_pt+1, to);
}


TEST_CASE("Unsorted ints", "quicksort"){
    std::vector<int> tst = {4,8,6,7,2,16,8981,23,7,1};
    quick_sort(tst, 0, tst.size());
    CHECK(std::is_sorted(tst.begin(), tst.end()));
    tst = {1,-6,323,-8,4,0,65,-4,2};
    quick_sort(tst, 0, tst.size());
    CHECK(std::is_sorted(tst.begin(), tst.end()));
}

TEST_CASE("Uniform ints", "quicksort"){
    std::vector<int> tst(15, 3);
    quick_sort(tst, 0, tst.size());
    CHECK(std::is_sorted(tst.begin(), tst.end()));
}

TEST_CASE("Sorted cases", "quicksort"){
    std::vector<int> tst = {1,2,3,4,5,6,7,8,8,9,20,50};
    quick_sort(tst, 0, tst.size());
    CHECK(std::is_sorted(tst.begin(), tst.end()));
    tst = {9,8,7,6,5,4,3,2,1};
    quick_sort(tst, 0, tst.size());
    CHECK(std::is_sorted(tst.begin(), tst.end()));
}


TEST_CASE("Strings", "quicksort"){
    std::vector<std::string> tst = {"one", "two", "three", "four", "five", "infinity"};
    quick_sort(tst, 0, tst.size());
    CHECK(std::is_sorted(tst.begin(), tst.end()));
}


TEST_CASE("Partial sort", "quicksort"){
    std::vector<int> tst = {8,8,0,0,46,58,2,3,87,13};
    for(size_t i=0; i<=tst.size();i++){
        quick_sort(tst, 0, i);
        auto it_end = tst.begin();
        std::advance(it_end, i);
        CHECK(std::is_sorted(tst.begin(), it_end));
    }
}
