#include <algorithm>
#include <vector>

struct PosVol {
  int position = 0;
  int volume = 0;
};

PosVol CalcLeftVolume(int pos, const std::vector<int>& height);
PosVol CalcRightVolume(int pos, const std::vector<int>& height);

class Solution {
 public:
  int trap(std::vector<int>& height) {
    int pos = std::max_element(height.begin(), height.end()) - height.begin();
    int volume = 0;
    int left = pos;
    while (left >= 0) {
      PosVol curr_res = CalcLeftVolume(left, height);
      left = curr_res.position;
      volume += curr_res.volume;
    }
    int right = pos;
    while (right < height.size()) {
      PosVol curr_res = CalcRightVolume(right, height);
      right = curr_res.position;
      volume += curr_res.volume;
    }
    return volume;
  }
};

PosVol CalcLeftVolume(int pos, const std::vector<int>& height) {
  if (pos == 0) return {-1, 0};
  int left_pos = pos;
  int filled = 0;
  while (left_pos > 0 && height[left_pos] >= height[left_pos - 1]) {
    --left_pos;
    filled += height[left_pos];
  }
  if (left_pos == 0) return {-1, 0};
  while (left_pos > 0 && height[left_pos] <= height[left_pos - 1]) {
    --left_pos;
    filled += height[left_pos];
  }
  filled -= height[left_pos];
  int empty =
      (pos - left_pos - 1) * std::min(height[pos], height[left_pos]) - filled;
  return {left_pos, empty};
}

PosVol CalcRightVolume(int pos, const std::vector<int>& height) {
  if (pos == height.size()) return {static_cast<int>(height.size()), 0};
  int right_pos = pos;
  int filled = 0;
  while (right_pos < height.size() - 1 &&
         height[right_pos] >= height[right_pos + 1]) {
    ++right_pos;
    filled += height[right_pos];
  }
  if (right_pos == height.size() - 1)
    return {static_cast<int>(height.size()), 0};
  while (right_pos < height.size() - 1 &&
         height[right_pos] <= height[right_pos + 1]) {
    ++right_pos;
    filled += height[right_pos];
  }
  filled -= height[right_pos];
  int empty =
      (right_pos - pos - 1) * std::min(height[pos], height[right_pos]) - filled;
  return {right_pos, empty};
}

int main() {
  Solution test;
  std::vector<int> input{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  test.trap(input);
  return 0;
}
