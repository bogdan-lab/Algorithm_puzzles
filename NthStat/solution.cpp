#include <vector>
#include <algorithm>
#include <string>
#include <random>

//#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>
#include<benchmark/benchmark.h>

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


size_t partition(std::vector<int>& vec, const size_t start, const size_t end){
    if(start==end) return start;
    auto l_idx = start;
    auto r_idx = end-1;
    while(true){
        while(l_idx<end && vec[l_idx]>=vec[end]) l_idx++;
        while(r_idx>start && vec[r_idx]<vec[end]) r_idx--;
        if(l_idx>=r_idx) break;
        std::swap(vec[l_idx], vec[r_idx]);
        l_idx++;
        r_idx--;
    }
    std::swap(vec[end], vec[l_idx]);
    return l_idx;
}


int get_nth_quick(std::vector<int> vec, const size_t el_num){
    size_t start = 0;
    auto end = vec.size()-1;
    auto res = partition(vec, start, end);
    while(res!=el_num){
        if(res>el_num){end = res-1;}
        else{start = res+1;}
        res = partition(vec, start, end);
    }
    return vec[res];
}



/*
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

TEST_CASE("Quick sort nth", "[quick]"){
    std::vector<int> tst2 = {12,6,87,98,5,3,9,45,6,8,79};
    CHECK(get_nth_quick(tst2, 0) == 98);
    CHECK(get_nth_quick(tst2, 1) == 87);
    CHECK(get_nth_quick(tst2, 2) == 79);
    CHECK(get_nth_quick(tst2, 3) == 45);
    CHECK(get_nth_quick(tst2, 4) == 12);
    CHECK(get_nth_quick(tst2, 5) == 9);
    CHECK(get_nth_quick(tst2, 6) == 8);
    CHECK(get_nth_quick(tst2, 7) == 6);
    CHECK(get_nth_quick(tst2, 8) == 6);
    CHECK(get_nth_quick(tst2, 9) == 5);
    CHECK(get_nth_quick(tst2, 10) == 3);

}
*/
std::vector<int> generate_rnd(const size_t size, const size_t seed){
    std::mt19937 rnd(seed);
    std::uniform_int_distribution<int> dist_val(-500, 500);
    std::vector<int> vec;
    vec.reserve(size);
    for(size_t i=0; i<size; i++){
      vec.push_back(dist_val(rnd));
    }
    return vec;
}

//BENCHMARKS

static void HeapNth_AVG(benchmark::State& state) {
  std::vector<int> vec = generate_rnd(10000, 42);
  std::mt19937 rnd(42u);
  std::uniform_int_distribution<size_t> dist_idx(0, vec.size()-1);
  for (auto _ : state) {
    get_nth_heap(vec, dist_idx(rnd));
  }
}


static void QuickNth_AVG(benchmark::State& state) {
  std::vector<int> vec = generate_rnd(10000, 42);
  std::mt19937 rnd(42u);
  std::uniform_int_distribution<size_t> dist_idx(0, vec.size()-1);
  for (auto _ : state) {
    get_nth_quick(vec, dist_idx(rnd));
  }
}

static void HeapNth_BEGIN(benchmark::State& state) {
  std::vector<int> vec = generate_rnd(10000, 42);
  std::mt19937 rnd(42u);
  std::uniform_int_distribution<size_t> dist_idx(0, 100);
  for (auto _ : state) {
    get_nth_heap(vec, dist_idx(rnd));
  }
}


static void QuickNth_BEGIN(benchmark::State& state) {
  std::vector<int> vec = generate_rnd(10000, 42);
  std::mt19937 rnd(42u);
  std::uniform_int_distribution<size_t> dist_idx(0, 100);
  for (auto _ : state) {
    get_nth_quick(vec, dist_idx(rnd));
  }
}

static void HeapNth_END(benchmark::State& state) {
  std::vector<int> vec = generate_rnd(10000, 42);
  std::mt19937 rnd(42u);
  std::uniform_int_distribution<size_t> dist_idx(vec.size()-100, vec.size()-1);
  for (auto _ : state) {
    get_nth_heap(vec, dist_idx(rnd));
  }
}


static void QuickNth_END(benchmark::State& state) {
  std::vector<int> vec = generate_rnd(10000, 42);
  std::mt19937 rnd(42u);
  std::uniform_int_distribution<size_t> dist_idx(vec.size()-100, vec.size()-1);
  for (auto _ : state) {
    get_nth_quick(vec, dist_idx(rnd));
  }
}

static void HeapNth_MID(benchmark::State& state) {
  std::vector<int> vec = generate_rnd(10000, 42);
  std::mt19937 rnd(42u);
  std::uniform_int_distribution<size_t> dist_idx(vec.size()/2-50, vec.size()/2+50);
  for (auto _ : state) {
    get_nth_heap(vec, dist_idx(rnd));
  }
}


static void QuickNth_MID(benchmark::State& state) {
  std::vector<int> vec = generate_rnd(10000, 42);
  std::mt19937 rnd(42u);
  std::uniform_int_distribution<size_t> dist_idx(vec.size()/2-50, vec.size()/2+50);
  for (auto _ : state) {
    get_nth_quick(vec, dist_idx(rnd));
  }
}


BENCHMARK(HeapNth_AVG);
BENCHMARK(QuickNth_AVG);

BENCHMARK(HeapNth_BEGIN);
BENCHMARK(QuickNth_BEGIN);

BENCHMARK(HeapNth_MID);
BENCHMARK(QuickNth_MID);

BENCHMARK(HeapNth_END);
BENCHMARK(QuickNth_END);


BENCHMARK_MAIN();




