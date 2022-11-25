#include <algorithm>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

bool IsPalindrome(std::string_view str) {
  for (int i = 0; i < str.size() / 2; ++i) {
    if (str[i] != str[str.size() - i - 1]) {
      return false;
    }
  }
  return true;
}

std::vector<std::vector<uint8_t>> BuildMap(std::string_view str) {
  std::vector<std::vector<uint8_t>> res(str.size(),
                                        std::vector<uint8_t>(str.size()));
  for (int i = 0; i < str.size(); ++i) {
    for (int j = i; j < str.size(); ++j) {
      if (IsPalindrome(str.substr(i, j - i + 1))) {
        res[i][j] = 1;
      }
    }
  }
  return res;
}

void GetMinSplits(const std::vector<std::vector<uint8_t>>& data, int idx,
                  int curr_count, int& min_count) {
  if (idx >= data.size()) {
    min_count = std::min(min_count, curr_count - 1);
    return;
  }

  for (int i = idx; i < data.size(); ++i) {
    if (data[idx][i]) {
      GetMinSplits(data, i + 1, curr_count + 1, min_count);
    }
  }
}

class Solution {
 public:
  int minCut(std::string s) {
    std::vector<std::vector<uint8_t>> data = BuildMap(s);
    int min_count = std::numeric_limits<int>::max();
    GetMinSplits(data, 0, 0, min_count);
    return min_count;
  }
};
