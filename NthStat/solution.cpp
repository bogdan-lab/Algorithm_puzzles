#include <vector>
#include <algorithm>
#include <string>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#define LEFT(x) 2*x+1
#define RIGHT(x) 2*x+2

void solve_heap_node(std::vector<int>& vec, size_t p_id){
    auto l_id = LEFT(p_id);
    auto r_id = RIGHT(p_id);
    if(l_id>=vec.size()) return;
    if(r_id==vec.size()){
        if(vec[l_id]<=vec[p_id]) return;
        std::swap(vec[p_id], vec[l_id]);
        solve_heap_node(vec, l_id);
        return;
    }
    auto max_id = vec[l_id]>vec[r_id] ? l_id : r_id;
    if(vec[p_id]>=vec[max_id]) return;
    std::swap(vec[p_id], vec[max_id]);
    solve_heap_node(vec, max_id);
    return;
}

void build_heap(std::vector<int>& vec){
    for(size_t i=vec.size()+1; i>0; i--){
        solve_heap_node(vec, i-1);
    }
}

int pop_max(std::vector<int>& vec){
    std::swap(vec.front(), vec.back());
    auto tmp = vec.back();
    vec.pop_back();
    solve_heap_node(vec, 0);
    return tmp;
}

int get_nth_heap(std::vector<int> vec, const size_t el_num){
    build_heap(vec);
    for(size_t i=0; i<el_num; i++){
        pop_max(vec);
    }
    return pop_max(vec);
}

TEST_CASE("Heap itself test", "[heap]"){
    std::vector<int> tst = {12,54,7,213,9,0,12,6,95,124,1};
    build_heap(tst);
    CHECK(std::is_heap(tst.begin(), tst.end()));
    std::vector<int> tst2 = {};
    build_heap(tst2);
    std::vector<int> tst3 = {1,1,1,1,1,1,1,1,1,1,1,1};
    build_heap(tst3);
    CHECK(std::is_heap(tst3.begin(), tst3.end()));
}

TEST_CASE("Heap nth test", "[heap]"){
    std::vector<int> tst2 = {12,6,87,98,5,3,9,45,6,8,79};
    CHECK(get_nth_heap(tst2, 0) == 98);
    CHECK(get_nth_heap(tst2, 1) == 87);
    CHECK(get_nth_heap(tst2, 2) == 79);
    CHECK(get_nth_heap(tst2, 3) == 45);
    CHECK(get_nth_heap(tst2, 4) == 12);
    CHECK(get_nth_heap(tst2, 5) == 9);
    CHECK(get_nth_heap(tst2, 6) == 8);
    CHECK(get_nth_heap(tst2, 7) == 6);
    CHECK(get_nth_heap(tst2, 8) == 6);
    CHECK(get_nth_heap(tst2, 9) == 5);
    CHECK(get_nth_heap(tst2, 10) == 3);
}
