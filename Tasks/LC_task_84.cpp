#include <algorithm>
#include <vector>

int MaxArea(const std::vector<int>& data, int max_h) {
  int max_area = 0;
  int curr_area = 0;
  for (const auto& el : data) {
    if (el < max_h) {
      max_area = std::max(max_area, curr_area);
      curr_area = 0;
    } else {
      curr_area += max_h;
    }
  }
  return std::max(curr_area, max_area);
}

class Solution {
 public:
  int largestRectangleArea(std::vector<int>& heights) {
    int max_h = *std::max_element(heights.begin(), heights.end());
    int max_area = 0;
    for (int h = 1; h <= max_h; ++h) {
      max_area = std::max(max_area, MaxArea(heights, h));
    }
    return max_area;
  }
};
