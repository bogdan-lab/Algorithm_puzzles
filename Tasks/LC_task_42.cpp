#include <algorithm>
#include <vector>

std::vector<int> GetPrefixMax(const std::vector<int>& data);
std::vector<int> GetSuffixMax(const std::vector<int>& data);

class Solution {
 public:
  int trap(std::vector<int>& height) {
    std::vector<int> prefix = GetPrefixMax(height);
    std::vector<int> suffix = GetSuffixMax(height);
    int volume = 0;
    for (size_t i = 0; i < prefix.size(); ++i) {
      volume += std::min(prefix[i], suffix[i]) - height[i];
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

