#include <algorithm>
#include <stack>
#include <vector>

std::vector<int> GetLeft(const std::vector<int>& data) {
  std::vector<int> res(data.size());
  std::stack<int> buff;
  for (int i = 0; i < data.size(); ++i) {
    while (!buff.empty() && data[buff.top()] >= data[i]) {
      buff.pop();
    }
    res[i] = buff.empty() ? -1 : buff.top();
    buff.push(i);
  }
  return res;
}

std::vector<int> GetRight(const std::vector<int>& data) {
  std::vector<int> res(data.size());
  std::stack<int> buff;
  for (int i = data.size() - 1; i >= 0; --i) {
    while (!buff.empty() && data[buff.top()] >= data[i]) {
      buff.pop();
    }
    res[i] = buff.empty() ? static_cast<int>(data.size()) : buff.top();
    buff.push(i);
  }
  return res;
}

int GetMaxAreaInHist(const std::vector<int>& data) {
  std::vector<int> left = GetLeft(data);
  std::vector<int> right = GetRight(data);

  int max_area = 0;
  for (int i = 0; i < data.size(); ++i) {
    max_area = std::max(max_area, data[i] * (right[i] - left[i] - 1));
  }
  return max_area;
}

class Solution {
 public:
  int maximalRectangle(std::vector<std::vector<char>>& matrix) {
    std::vector<int> hist(matrix[0].size());
    int max_area = 0;
    for (int r = 0; r < matrix.size(); ++r) {
      for (int i = 0; i < matrix[r].size(); ++i) {
        if (matrix[r][i] == '1') {
          ++hist[i];
        } else {
          hist[i] = 0;
        }
      }
      max_area = std::max(max_area, GetMaxAreaInHist(hist));
    }
    return max_area;
  }
};
