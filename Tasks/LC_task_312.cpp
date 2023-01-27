#include <algorithm>
#include <array>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

struct Node {
  std::array<int, 3> vals;
  std::array<int, 3> indexes;
};

int Calc(const Node& x) { return x.vals[0] * x.vals[1] * x.vals[2]; }

int CalcRem(const Node& x) {
  int l = x.vals[0];
  int r = x.vals[2];
  if (l > r) std::swap(l, r);
  return (l + 1) * r;
}

bool HasInvalidIndex(const Node& n, const std::vector<int>& lookup) {
  return lookup[n.indexes[0]] || lookup[n.indexes[1]] || lookup[n.indexes[2]];
}

struct NodeSmaller {
  bool operator()(const Node& l, const Node& r) const {
    int cl = Calc(l);
    int cr = Calc(r);
    int rem_l = CalcRem(l);
    int rem_r = CalcRem(r);
    return std::tie(cl, rem_l) < std::tie(cr, rem_r);
  }
};

using MaxQueue = std::priority_queue<Node, std::vector<Node>, NodeSmaller>;

class Solution {
 public:
  int maxCoins(vector<int>& nums) {
    nums.push_back(1);
    std::rotate(nums.begin(), std::prev(nums.end()), nums.end());
    nums.push_back(1);

    MaxQueue buff;
    for (int i = 1; i < nums.size() - 1; ++i) {
      buff.push({{nums[i - 1], nums[i], nums[i + 1]}, {i - 1, i, i + 1}});
    }

    int count = nums.size() - 2;
    std::vector<int> lookup(nums.size());
    int res = 0;
    while (count) {
      while (HasInvalidIndex(buff.top(), lookup)) {
        buff.pop();
      }
      res += Calc(buff.top());
      int d = buff.top().indexes[1];
      if (d - 2 >= 0) {
        buff.push(
            {{nums[d - 2], nums[d - 1], nums[d + 1]}, {d - 2, d - 1, d + 1}});
      }
      if (d + 2 < nums.size()) {
        buff.push(
            {{nums[d - 1], nums[d + 1], nums[d + 2]}, {d - 1, d + 1, d + 2}});
      }
      lookup[d] = 1;
      --count;
    }
    return res;
  }
};
