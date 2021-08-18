#include <vector>
#include <algorithm>
#include <string>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>


size_t convert_s_to_i(const std::string& s, const size_t col_idx);
size_t get_max_str_len(const std::vector<std::string>& vec);
void stable_sort_by_col(std::vector<std::string>& vec, size_t col_idx);
void radix_string_sort(std::vector<std::string>& vec);
std::vector<size_t> count_sort(const std::vector<size_t>& vec);
void inplace_count_sort(std::vector<size_t>& vec);
size_t get_max_el(const std::vector<std::string>& vec, const size_t col_idx);
std::vector<size_t> count_elements(const std::vector<std::string>& vec, const size_t col_idx);
void particular_count_sort(std::vector<std::string>& vec, const size_t col_idx,
                           const size_t start, const size_t end);


size_t convert_s_to_i(const std::string& s, const size_t col_idx){
    if(col_idx>s.size()) exit(1);
    return static_cast<size_t>(s[col_idx]);
}

size_t get_max_str_len(const std::vector<std::string>& vec){
    size_t max_len = 0;
    for(const auto& el : vec){
        max_len = std::max(el.size(),max_len);
    }
    return max_len;
}

void stable_sort_by_col(std::vector<std::string>& vec, size_t col_idx){
    std::stable_sort(vec.begin(), vec.end(),
                     [&](const std::string& lhs, const std::string& rhs){
        size_t l_c = convert_s_to_i(lhs, col_idx);
        size_t r_c = convert_s_to_i(rhs, col_idx);
        return l_c<r_c;
    });
}

std::vector<size_t> count_sort_by_size(std::vector<std::string>& vec){
    size_t max_str_len = get_max_str_len(vec);
    std::vector<size_t> count_by_size(max_str_len+1, 0);
    for(size_t i=0; i<vec.size(); i++){
        count_by_size[vec[i].size()]++;
    }
    for(size_t i=0; i<count_by_size.size()-1; i++){
        count_by_size[i+1] += count_by_size[i];
    }
    std::vector<size_t> tmp = count_by_size;
    std::vector<size_t> correct_idx(vec.size(), 0u);
    for(size_t i=vec.size(); i>0; i--){
        size_t val = vec[i-1].size();
        correct_idx[i-1] = tmp[val]-1;
        tmp[val]--;
    }
    for(size_t i=0; i<vec.size(); i++){
        size_t move_to = correct_idx[i];
        while(move_to != i){
            std::swap(vec[move_to], vec[i]);
            std::swap(correct_idx[i], correct_idx[move_to]);
            move_to = correct_idx[i];
        }
    }
    return count_by_size;
}

void radix_string_sort(std::vector<std::string>& vec){
    std::vector<size_t> count_by_size = count_sort_by_size(vec);
    //here all strings are sorted by length and count_by_size contains info about
    //where and how many of those strings we have
    for(size_t i=0; i<count_by_size.size()-1; i++){
        if(count_by_size[i]==count_by_size[i+1]) continue;
        size_t start = count_by_size[i];
        size_t end = count_by_size[i+1];
        size_t str_size = i+1;
        for(size_t j=str_size; j>0; j--){
            particular_count_sort(vec, j-1, start, end);
        }
    }
}

std::vector<size_t> count_sort(const std::vector<size_t>& vec){
    if(vec.empty()) return {};
    size_t max_el = *(std::max_element(vec.begin(), vec.end()));
    std::vector<size_t> count_idx(max_el+1, 0);
    for(size_t i=0; i<vec.size(); i++){
        count_idx[vec[i]]++;
    }
    for(size_t i=0; i<count_idx.size()-1; i++){
        count_idx[i+1]+=count_idx[i];
    }
    std::vector<size_t> sorted(vec.size(), 0);
    for(size_t i=vec.size(); i>0; i--){
        size_t idx = count_idx[vec[i-1]]-1;
        sorted[idx] = vec[i-1];
        count_idx[vec[i-1]]--;
    }
    return sorted;
}


void inplace_count_sort(std::vector<size_t>& vec){
    if(vec.empty()) return;
    size_t max_el = *(std::max_element(vec.begin(), vec.end()));
    std::vector<size_t> count_idx(max_el+1, 0);
    for(size_t i=0; i<vec.size(); i++){
        count_idx[vec[i]]++;
    }
    for(size_t i=0; i<count_idx.size()-1; i++){
        count_idx[i+1]+=count_idx[i];
    }
    std::vector<size_t> correct_idx(vec.size(), 0);
    for(size_t i=vec.size(); i>0; i--){
        correct_idx[i-1] = count_idx[vec[i-1]]-1;
        count_idx[vec[i-1]]--;
    }
    for(size_t i=0; i<vec.size(); i++){
        size_t move_idx = correct_idx[i];
        while(move_idx!=i){
            std::swap(vec[i], vec[move_idx]);
            std::swap(correct_idx[i], correct_idx[move_idx]);
            move_idx = correct_idx[i];
        }
    }
}


size_t get_max_el(const std::vector<std::string>& vec, const size_t col_idx,
                  const size_t start, const size_t end){
    size_t max_el = 0;
    for(size_t i=start; i<end; i++){
        size_t num = convert_s_to_i(vec[i], col_idx);
        if(num>max_el) max_el = num;
    }
    return max_el;
}

std::vector<size_t> count_elements(const std::vector<std::string>& vec, const size_t col_idx,
                                   const size_t start, const size_t end){
    size_t max_el = get_max_el(vec, col_idx, start, end);
    std::vector<size_t> count_idx(max_el+1, 0);
    for(size_t i=start; i<end; i++){
        size_t idx = convert_s_to_i(vec[i], col_idx);
        count_idx[idx]++;
    }
    return count_idx;
}

void particular_count_sort(std::vector<std::string>& vec, const size_t col_idx,
                           const size_t start, const size_t end){
    if(vec.size()<=1) return;
    std::vector<size_t> count_idx = count_elements(vec, col_idx, start, end);
    for(size_t i=0; i<count_idx.size()-1; i++){
        count_idx[i+1]+=count_idx[i];
    }
    std::vector<size_t> correct_idx(vec.size(), 0);
    for(size_t i=end; i>start; i--){
        size_t idx = convert_s_to_i(vec[i-1], col_idx);
        correct_idx[i-1] = start + count_idx[idx]-1;
        count_idx[idx]--;
    }
    for(size_t i=start; i<end; i++){
        size_t move_idx = correct_idx[i];
        while(move_idx!=i){
            std::swap(vec[i], vec[move_idx]);
            std::swap(correct_idx[i], correct_idx[move_idx]);
            move_idx = correct_idx[i];
        }
    }
}

bool my_compare(const std::string& lhs, const std::string& rhs){
    if(lhs.size()==rhs.size()) return lhs<rhs;
    return lhs.size()<rhs.size();
}


TEST_CASE("Equal length test", "[]"){
    std::vector<std::string> tst = {"dd", "bb", "aa", "cc", "hh", "jj", "kk"};
    radix_string_sort(tst);
    CHECK(std::is_sorted(tst.begin(), tst.end(), my_compare));
    std::vector<std::string> tst1 = {"as", "sd", "al", "aa", "am", "ak", "ab"};
    radix_string_sort(tst1);
    CHECK(std::is_sorted(tst1.begin(), tst1.end(), my_compare));
    std::vector<std::string> tst2;
    radix_string_sort(tst2);
    CHECK(std::is_sorted(tst2.begin(), tst2.end(), my_compare));
    std::vector<std::string> tst3 = {"a","a", "a", "a", "a", "a", "a", "a", "a", "a" };
    radix_string_sort(tst3);
    CHECK(std::is_sorted(tst3.begin(), tst3.end(), my_compare));
    std::vector<std::string> tst4 = {"name"};
    radix_string_sort(tst4);
    CHECK(std::is_sorted(tst4.begin(), tst4.end(), my_compare));
}

TEST_CASE("Different length test", "[]"){
    std::vector<std::string> tst = {"a", "ba", "ajfdsa", "adl", "aaa", "bfd", "b"};
    std::sort(tst.begin(), tst.end());
    radix_string_sort(tst);
    CHECK(std::is_sorted(tst.begin(), tst.end(), my_compare));
    std::vector<std::string> tst1 = {"This", "task", "is", "finished", "without",
                                    "generalizing", "approach", "!", "anyway",
                                     "I", "am", "happy", "with", "it"};
    radix_string_sort(tst1);
    CHECK(std::is_sorted(tst1.begin(), tst1.end(), my_compare));
}

TEST_CASE("Test counting sort", "[]"){
    std::vector<size_t> tst = {3,6,1,3,8,9,4,0,0,12,5};
    std::vector<size_t> got = count_sort(tst);
    CHECK(std::is_sorted(got.begin(), got.end()));
    std::vector<size_t> tst1;
    std::vector<size_t> got1=count_sort(tst1);
    CHECK(std::is_sorted(got1.begin(), got1.end()));
    std::vector<size_t> tst2 = {1,1,1,1,1,1,1,1,1,1};
    std::vector<size_t> got2 = count_sort(tst2);
    CHECK(std::is_sorted(got2.begin(), got2.end()));
}

TEST_CASE("Test in-pace-counting sort", "[]"){
    std::vector<size_t> tst = {3,6,1,3,8,9,4,0,0,12,5};
    inplace_count_sort(tst);
    CHECK(std::is_sorted(tst.begin(), tst.end()));
    std::vector<size_t> tst1;
    inplace_count_sort(tst1);
    CHECK(std::is_sorted(tst1.begin(), tst1.end()));
    std::vector<size_t> tst2 = {1,1,1,1,1,1,1,1,1,1};
    inplace_count_sort(tst2);
    CHECK(std::is_sorted(tst2.begin(), tst2.end()));
}
