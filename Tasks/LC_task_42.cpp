#include <algorithm>
#include <vector>

std::vector<int> GetPrefixMax(const std::vector<int>& data);
std::vector<int> GetSuffixMax(const std::vector<int>& data);

class Solution {
 public:
  int trap(std::vector<int>& height) {
    int pos = std::max_element(height.begin(), height.end()) - height.begin();
    int volume = 0;
    // accumulate to the left
    std::vector<int> prefix = GetPrefixMax(height);
    int start = pos;
    while (start > 0) {
      int end_val = prefix[start - 1];
      int curr_pos = start;
      int filled = 0;
      while (height[curr_pos - 1] != end_val) {
        --curr_pos;
        filled += height[curr_pos];
      }
      volume += (start - curr_pos) * end_val - filled;
      start = curr_pos - 1;
    }
    // accumulate to the right
    std::vector<int> suffix = GetSuffixMax(height);
    start = pos;
    while (start < height.size() - 1) {
      int end_val = suffix[start + 1];
      int curr_pos = start;
      int filled = 0;
      while (height[curr_pos + 1] != end_val) {
        ++curr_pos;
        filled += height[curr_pos];
      }
      volume += (curr_pos - start) * end_val - filled;
      start = curr_pos + 1;
    }
    return volume;
  }
};

std::vector<int> GetPrefixMax(const std::vector<int>& data) {
  std::vector<int> res(data.size());
  res[0] = data[0];
  for (size_t i = 1; i < res.size(); ++i) {
    res[i] = std::max(res[i - 1], data[i]);
  }
  return res;
}

std::vector<int> GetSuffixMax(const std::vector<int>& data) {
  std::vector<int> res(data.size());
  res.back() = data.back();
  auto rit = res.rbegin();
  auto dit = ++data.rbegin();
  while (dit != data.rend()) {
    auto it = std::next(rit);
    *it = std::max(*rit, *dit);
    rit = it;
    ++dit;
  }
  return res;
}

