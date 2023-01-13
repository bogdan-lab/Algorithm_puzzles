#include <algorithm>
#include <cassert>
#include <limits>
#include <stack>
#include <vector>

void ClearStack(std::vector<std::vector<int>>& stk,
                std::vector<std::vector<int>>& res, int64_t next_left) {
  while (!stk.empty() && stk.back()[1] <= next_left) {
    const auto& top = stk.back();
    if (stk.size() > 1) {
      const auto& prev = stk[stk.size() - 2];
      if (prev[1] > top[1]) {
        res.push_back({top[1], prev[2]});
      } else {
        std::swap(stk.back(), stk[stk.size() - 2]);
        // Here we do nothing and pop in the end of the loop
        // We need to find the next highest building with edge futher on right.
      }
    } else {
      if (top[1] < next_left) {
        res.push_back({top[1], 0});
      }
    }

    stk.pop_back();
  }
}

void ExpandEqualHeights(std::vector<int>& lb, std::vector<int>& rb) {
  assert(lb[2] == rb[2]);
  int ml = std::min(lb[0], rb[0]);
  int mr = std::max(rb[1], lb[1]);
  lb[0] = rb[0] = ml;
  lb[1] = rb[1] = mr;
}

void PushBuilding(std::vector<std::vector<int>>& stk,
                  const std::vector<int>& b) {
  stk.push_back(b);
  if (stk.size() == 1) return;
  int i = stk.size() - 2;
  while (i >= 0 && stk[i][2] > b[2]) {
    std::swap(stk[i], stk[i + 1]);
    --i;
  }
  while (i >= 0 && stk[i][2] == b[2]) {
    ExpandEqualHeights(stk[i], stk[i + 1]);
    --i;
  }
}

class Solution {
 public:
  std::vector<std::vector<int>> getSkyline(
      std::vector<std::vector<int>>& buildings) {
    std::vector<std::vector<int>> stk;
    std::vector<std::vector<int>> res;
    int i = 0;
    while (i < buildings.size()) {
      ClearStack(stk, res, buildings[i][0]);
      // Here in the stk we have sorted by height buildings, which crossect the
      // start of current building
      // Now we push all buildings with current left boarder, while keeping the
      // stk sorted
      int initial_left = buildings[i][0];
      while (i < buildings.size() && buildings[i][0] == initial_left) {
        PushBuilding(stk, buildings[i]);
        ++i;
      }
      if (res.empty() || res.back()[1] != stk.back()[2]) {
        res.push_back({initial_left, stk.back()[2]});
      }
    }
    ClearStack(stk, res, std::numeric_limits<int64_t>::max());
    return res;
  }
};
