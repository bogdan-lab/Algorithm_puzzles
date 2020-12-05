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
        return lhs[col_idx]<rhs[col_idx];
    });
}

void radix_string_sort(std::vector<std::string>& vec){
    size_t max_str_len = get_max_str_len(vec);
    for(size_t i=max_str_len; i>0; i--){
        stable_sort_by_col(vec, i-1);
    }
}




TEST_CASE("Equal length test", "[]"){
    std::vector<std::string> tst = {"dd", "bb", "aa", "cc", "hh", "jj", "kk"};
    radix_string_sort(tst);
    CHECK(std::is_sorted(tst.begin(), tst.end()));
    std::vector<std::string> tst1 = {"as", "sd", "al", "aa", "am", "ak", "ab"};
    radix_string_sort(tst1);
    CHECK(std::is_sorted(tst1.begin(), tst1.end()));
}


TEST_CASE("Different length", "[]"){

}
