#include <utility>
#include <vector>

std::vector<std::pair<int, int>> Merge(
    const std::vector<std::pair<int, int>>& lhs,
    const std::vector<std::pair<int, int>>& rhs, std::vector<int>& res) {
  int count = 0;
  int l = 0;
  int r = 0;
  std::vector<std::pair<int, int>> merged;
  merged.reserve(lhs.size() + rhs.size());
  while (l < lhs.size() || r < rhs.size()) {
    if (l >= lhs.size()) {
      merged.push_back(rhs[r]);
      ++r;
    } else if (r >= rhs.size()) {
      merged.push_back(lhs[l]);
      res[lhs[l].second] += count;
      ++l;
    } else {
      if (lhs[l].first <= rhs[r].first) {
        merged.push_back(lhs[l]);
        res[lhs[l].second] += count;
        ++l;
      } else {
        merged.push_back(rhs[r]);
        ++r;
        ++count;
      }
    }
  }
  return merged;
}

std::vector<std::pair<int, int>> BuildData(const std::vector<int>& nums) {
  std::vector<std::pair<int, int>> data;
  data.reserve(nums.size());
  for (int i = 0; i < nums.size(); ++i) {
    data.push_back({nums[i], i});
  }
  return data;
}

std::vector<std::pair<int, int>> CalcAnswer(
    const std::vector<std::pair<int, int>>& data, int begin, int end,
    std::vector<int>& res) {
  if (end - begin <= 1) {
    return {data.begin() + begin, data.begin() + end};
  }
  int mid = (begin + end) / 2;
  return Merge(CalcAnswer(data, begin, mid, res),
               CalcAnswer(data, mid, end, res), res);
}

class Solution {
 public:
  std::vector<int> countSmaller(std::vector<int>& nums) {
    auto data = BuildData(nums);
    std::vector<int> res(nums.size());
    CalcAnswer(data, 0, data.size(), res);
    return res;
  }
};
