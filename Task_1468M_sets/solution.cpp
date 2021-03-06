﻿#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_set>
#include <random>
#include <time.h>
#include <utility>
#include <chrono>

template <size_t N, size_t M>
class MyHashTable{
private:
    std::vector<int> data_;
    std::vector<int> buckets_;
    size_t mod_;
    size_t size_;
    bool sorted_;

    size_t get_next(size_t i) const {return i*i; }
public:
    MyHashTable() = delete;
    MyHashTable(size_t size): size_(size){
        if(size > N){
            buckets_ = std::vector<int>(M*size, -1);
            mod_ = M*size;
        }
        sorted_ = false;
        data_.reserve(size);
    }

    void insert(int val){
        data_.push_back(val);
        if (size_ > N){
            size_t i=1;
            size_t idx = static_cast<size_t>(val) % mod_;
            while(buckets_[idx]!=-1){
                idx += get_next(i);
                while(idx >= buckets_.size()) idx-=buckets_.size();
                i++;
            }
            buckets_[idx] = val;
        }
    }

    size_t count_hash(const int val) const {
        size_t idx = static_cast<size_t>(val) % mod_;
        size_t i=1;
        while(buckets_[idx]!=-1){
            if(buckets_[idx]==val) return 1;
            idx += get_next(i);
            while(idx>=buckets_.size()) idx-=buckets_.size();
            i++;
        }
        return 0;
    }

    size_t count(const int val) const{
        if(size_>N){
            return count_hash(val);
        }
        return static_cast<size_t>(std::binary_search(data_.begin(), data_.end(), val));
    }

    void sort_data(){
        if(size_<= N){
            std::sort(data_.begin(), data_.end());
            sorted_ = true;
        }
    }

    bool is_sorted() const {
        return sorted_;
    }

    auto begin() const {return data_.begin();}
    auto end() const {return data_.end();}

};

using ElCollection = MyHashTable<10, 7>;
using SetHolder = std::vector<ElCollection>;

bool compare_two_sets(const ElCollection& lhs, const ElCollection& rhs);
void fill_minmax_stat(std::vector<int>& min_el, std::vector<int>& max_el,
                      const SetHolder& entire_set);
std::string process_set(std::mt19937& rnd, std::istream& input=std::cin);
void solve(std::mt19937& rnd, std::istream& input=std::cin);
std::stringstream prepare_test(std::mt19937& rnd, const size_t t,
                               const size_t n, const size_t k);
void fill_random_numbers(std::stringstream& ss, const size_t k, std::mt19937& rnd);


int main(){
    std::ios_base::sync_with_stdio (false);
    std::cin.tie(nullptr);
    std::stringstream ss;
    ss << R"(3
          4
          2 1 10
          3 1 3 5
          5 5 4 3 2 1
          3 10 20 30
          3
          4 1 2 3 4
          4 2 3 4 5
          4 3 4 5 6
          2
          3 1 3 5
          3 4 3 2)";
    std::mt19937 rnd(static_cast<unsigned int>(time(NULL)));
/*
    std::stringstream test = prepare_test(rnd, 1, 2000, 100);
    auto start = std::chrono::high_resolution_clock::now();
    solve(rnd, test);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout << "\n test duration = " << duration.count() << " ms ; NEED <1000ms!!\n";
*/
    solve(rnd, std::cin);
    return 0;
}


std::stringstream prepare_test(std::mt19937& rnd, const size_t t,
                               const size_t n, const size_t k){
    std::stringstream ss;
    ss << t << '\n';
    ss << n << '\n';
    for(size_t i=0; i<n; i++){
        ss << k;
        fill_random_numbers(ss, k, rnd);
    }
    return ss;
}

void fill_random_numbers(std::stringstream& ss, const size_t k, std::mt19937& rnd){
    std::uniform_int_distribution<size_t> dist(1, 1000'000'000);
    for(size_t i=0; i<k; i++){
        ss << ' ' << dist(rnd);
    }
    ss << '\n';
}

bool compare_two_sets(const ElCollection& lhs, const ElCollection& rhs){
    size_t dup_num = 0;
    for(const auto& el : lhs){
        dup_num += rhs.count(el);
        if(dup_num>=2) return true;
    }
    return false;
}


void fill_minmax_stat(std::vector<int>& min_el, std::vector<int>& max_el,
                      const SetHolder& entire_set){
    for(size_t i=0; i<entire_set.size(); i++){
        if(entire_set[i].is_sorted()){
            min_el[i] = *(entire_set[i].begin());
            max_el[i] = *(--entire_set[i].end());
        }else {
            auto it = std::minmax_element(entire_set[i].begin(), entire_set[i].end());
            min_el[i] = *(it.first);
            max_el[i] = *(it.second);
        }
    }
}

std::string process_set(std::mt19937& rnd, std::istream& input){
    size_t n;
    size_t k;
    input >> n;
    SetHolder entire_set;
    entire_set.reserve(n);
    int tmp;
    for(size_t i=0; i<n; i++){ 	 	//O(n)
        input >> k;
        ElCollection current_set(k);
        for(size_t j=0; j<k; j++){
            input >> tmp;
            current_set.insert(tmp);
        }
        current_set.sort_data();
        entire_set.push_back(current_set);
    }
    std::vector<int> minimum_el_in_set(n);
    std::vector<int> maximum_el_in_set(n);
    fill_minmax_stat(minimum_el_in_set, maximum_el_in_set, entire_set); 	//O(n)
    //For better average performance
    std::vector<size_t> idxes(n);
    std::iota(idxes.begin(), idxes.end(), 0);
    std::shuffle(idxes.begin(), idxes.end(), rnd); 	 	 	//O(n)
    //Check for pair
    for(size_t i=0; i<n; i++){
        size_t lhs_idx = idxes[i];
        for(size_t j=i+1; j<n; j++){
            size_t rhs_idx = idxes[j];
            if(maximum_el_in_set[lhs_idx]>minimum_el_in_set[rhs_idx]
               && maximum_el_in_set[rhs_idx]>minimum_el_in_set[lhs_idx]
               && compare_two_sets(entire_set[lhs_idx], entire_set[rhs_idx])){
                return std::to_string(lhs_idx+1) + " " + std::to_string(rhs_idx+1) + "\n";
            }
        }
    }
    return "-1\n";
}

void solve(std::mt19937& rnd, std::istream& input){
    size_t t;
    input >> t;
    for(size_t i=0; i<t; i++){
        std::cout << process_set(rnd, input);
    }
}

