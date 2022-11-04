#include <algorithm>
#include <bitset>
#include <vector>

constexpr int kMaxSize = 200;

std::bitset<kMaxSize> ToBitSet(const std::vector<char>& data) {
  std::bitset<kMaxSize> res;
  for (int i = 0; i < data.size(); ++i) {
    if (data[i] == '1') {
      res.set(i);
    }
  }
  return res;
}

class Solution {
 public:
  int maximalRectangle(std::vector<std::vector<char>>& matrix) {
    std::vector<std::bitset<kMaxSize>> rows;
    rows.reserve(matrix.size());
    for (int i = 0; i < matrix.size(); ++i) {
      rows.push_back(ToBitSet(matrix[i]));
    }

    int max_num = 0;
    for (int w = 0; w < rows.size(); ++w) {
      for (int i = 0; i < rows.size() - w; ++i) {
        if (i + w >= rows.size()) break;
        std::bitset<kMaxSize> curr = rows[i];
        for (int j = i + 1; j <= i + w; ++j) {
          curr &= rows[j];
        }
        max_num = std::max<int>(max_num, (w + 1) * curr.count());
      }
    }
    return max_num;
  }
};
