#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>

struct HeightCompare {
  bool operator()(const std::vector<int>& lb, const std::vector<int>& rb) {
    return std::tie(lb[2], lb[1]) < std::tie(rb[2], rb[1]);
  }
};

using BuildingQueue =
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>,
                        HeightCompare>;

void ClearStack(BuildingQueue& stk, std::vector<std::vector<int>>& res,
                int64_t next_left) {
  while (!stk.empty() && stk.top()[1] <= next_left) {
    auto top = stk.top();
    stk.pop();
    while (!stk.empty() && stk.top()[1] <= top[1]) {
      stk.pop();
    }
    if (stk.empty()) {
      if (top[1] < next_left) {
        res.push_back({top[1], 0});
      }
    } else {
      res.push_back({top[1], stk.top()[2]});
    }
  }
}

class Solution {
 public:
  std::vector<std::vector<int>> getSkyline(
      std::vector<std::vector<int>>& buildings) {
    BuildingQueue stk;
    std::vector<std::vector<int>> res;
    int i = 0;
    while (i < buildings.size()) {
      ClearStack(stk, res, buildings[i][0]);
      int initial_left = buildings[i][0];
      while (i < buildings.size() && buildings[i][0] == initial_left) {
        stk.push(buildings[i]);
        ++i;
      }
      if (res.empty() || res.back()[1] != stk.top()[2]) {
        res.push_back({initial_left, stk.top()[2]});
      }
    }
    ClearStack(stk, res, std::numeric_limits<int64_t>::max());
    return res;
  }
};
