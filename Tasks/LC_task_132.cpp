#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

void CheckRowFor(std::string_view str, int i,
                 std::vector<std::vector<uint8_t>>& res) {
  int j = i;
  res[i][j] = 1;
  bool prev_even = true;
  bool prev_odd = true;
  while (true) {
    --i;
    if (i < 0) break;
    if (str[i] == str[j] && prev_even) {
      res[i][j] = 1;
    } else {
      prev_even = false;
    }
    ++j;
    if (j == res.size()) break;
    if (str[i] == str[j] && prev_odd) {
      res[i][j] = 1;
    } else {
      prev_odd = false;
    }
  }
}

std::vector<std::vector<uint8_t>> BuildMap(std::string_view str) {
  std::vector<std::vector<uint8_t>> res(str.size(),
                                        std::vector<uint8_t>(str.size()));
  for (int i = 0; i < str.size(); ++i) {
    CheckRowFor(str, i, res);
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

int main() {
  Solution s;
  int res = s.minCut("ababababababababababababcbabababababababababababa");
  std::cout << res << '\n';
  return 0;
}
