#include <algorithm>
#include <stack>
#include <vector>

struct PosHeight {
  int pos = 0;
  int height = 0;
};

int GetMaxArea(const std::vector<int>& data) {
  int max_area = 0;
  std::stack<PosHeight> buff;
  for (int i = 0; i < data.size(); ++i) {
    while (!buff.empty() && data[i] < buff.top().height) {
      max_area = std::max(max_area, buff.top().height * (i - buff.top().pos));
      buff.pop();
    }
    int prev_h = buff.empty() ? 0 : buff.top().height;
    for (int h = prev_h + 1; h <= data[i]; ++h) {
      buff.push({.pos = i, .height = h});
    }
  }
  while (!buff.empty()) {
    max_area = std::max<int>(
        max_area, buff.top().height * (data.size() - buff.top().pos));
    buff.pop();
  }
  return max_area;
}

class Solution {
 public:
  int largestRectangleArea(std::vector<int>& heights) {
    int max_area = GetMaxArea(heights);
    std::reverse(heights.begin(), heights.end());
    return std::max(max_area, GetMaxArea(heights));
  }
};
