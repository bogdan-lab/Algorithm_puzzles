#include <algorithm>
#include <stack>
#include <vector>

struct PosHeight {
  int pos = 0;
  int height = 0;
};

std::vector<int> GetClosestSmallerOnTheLeft(const std::vector<int>& data) {
  std::stack<PosHeight> buff;
  buff.push({.pos = -1, .height = -1});
  std::vector<int> res(data.size());
  for (int i = 0; i < data.size(); ++i) {
    while (buff.top().height >= data[i]) {
      buff.pop();
    }
    res[i] = buff.top().pos;
    buff.push({.pos = i, .height = data[i]});
  }
  return res;
}

std::vector<int> GetClosestSmallerOnTheRight(const std::vector<int>& data) {
  std::stack<PosHeight> buff;
  buff.push({.pos = static_cast<int>(data.size()), .height = -1});
  std::vector<int> res(data.size());
  for (int i = data.size() - 1; i >= 0; --i) {
    while (buff.top().height >= data[i]) {
      buff.pop();
    }
    res[i] = buff.top().pos;
    buff.push({.pos = i, .height = data[i]});
  }
  return res;
}

class Solution {
 public:
  int largestRectangleArea(std::vector<int>& heights) {
    std::vector<int> left = GetClosestSmallerOnTheLeft(heights);
    std::vector<int> right = GetClosestSmallerOnTheRight(heights);
    int max_area = 0;
    for (int i = 0; i < heights.size(); ++i) {
      max_area = std::max(max_area, heights[i] * (right[i] - left[i] - 1));
    }
    return max_area;
  }
};
