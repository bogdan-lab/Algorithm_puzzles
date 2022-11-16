#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Solution {
 public:
  bool isScramble(std::string s1, std::string s2) {
    assert(s1.size() == s2.size());
    std::vector<std::vector<std::vector<int>>> data(s1.size());
    for (auto& el : data) {
      el.resize(s1.size());
      for (auto& item : el) {
        item.resize(s1.size());
      }
    }

    for (size_t i = 0; i < s1.size(); ++i) {
      for (size_t j = 0; j < s1.size(); ++j) {
        data[i][j][0] = (s1[i] == s2[j]);
      }
    }

    for (size_t l = 1; l < s1.size(); ++l) {
      for (size_t i = 0; i < s1.size() - l; ++i) {
        for (size_t j = 0; j < s1.size() - l; ++j) {
          for (size_t w = 0; w < l; ++w) {
            if ((data[i][j][w] && data[i + w + 1][j + w + 1][l - w - 1]) ||
                (data[i][j + l - w][w] && data[i + w + 1][j][l - w - 1])) {
              data[i][j][l] = 1;
              break;
            }
          }
        }
      }
    }
    return data[0][0][s1.size() - 1];
  }
};

int main() {
  Solution s;
  assert(!s.isScramble("abcde", "caebd"));
  assert(s.isScramble("abcdbdacbdac", "bdacabcdbdac"));
  assert(s.isScramble("abc", "bca"));
  return 0;
}
