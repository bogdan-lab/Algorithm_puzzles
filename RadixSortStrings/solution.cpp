#include <vector>
#include <algorithm>
#include <string>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

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
        char l_c = col_idx<lhs.size() ? lhs[col_idx] : static_cast<char>(0u);
        char r_c = col_idx<rhs.size() ? rhs[col_idx] : static_cast<char>(0u);
        return l_c<r_c;
    });
}

void radix_string_sort(std::vector<std::string>& vec){
    size_t max_str_len = get_max_str_len(vec);
    for(size_t i=max_str_len; i>0; i--){
        stable_sort_by_col(vec, i-1);
    }
}

std::vector<size_t> count_sort(const std::vector<size_t>& vec){
    //Cannot be inplace...
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


TEST_CASE("Equal length test", "[]"){
    std::vector<std::string> tst = {"dd", "bb", "aa", "cc", "hh", "jj", "kk"};
    radix_string_sort(tst);
    CHECK(std::is_sorted(tst.begin(), tst.end()));
    std::vector<std::string> tst1 = {"as", "sd", "al", "aa", "am", "ak", "ab"};
    radix_string_sort(tst1);
    CHECK(std::is_sorted(tst1.begin(), tst1.end()));
    std::vector<std::string> tst2;
    radix_string_sort(tst2);
    CHECK(std::is_sorted(tst2.begin(), tst2.end()));
}

TEST_CASE("Different length test", "[]"){
    std::vector<std::string> tst = {"a", "ba", "ajfdsa", "adl", "aaa", "bfd", "b"};
    radix_string_sort(tst);
    CHECK(std::is_sorted(tst.begin(), tst.end()));
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
