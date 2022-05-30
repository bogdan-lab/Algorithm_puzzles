#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class Solution {
 public:
  int firstMissingPositive(std::vector<int>& nums) {
    int size = nums.size();
    for (int i = 0; i < size; ++i) {
      if (nums[i] <= 0) continue;
      if (nums[i] > size) {
        nums[i] = 0;
        continue;
      }
      while (nums[i] > 0 && nums[i] <= size && nums[i] - 1 != i) {
        int pos = nums[i] - 1;
        if (nums[pos] - 1 == pos) {
          nums[i] = 0;
        } else {
          std::swap(nums[i], nums[nums[i] - 1]);
        }
      }
      if (nums[i] > size) {
        nums[i] = 0;
      }
    }
    auto it = std::find_if(nums.begin(), nums.end(),
                           [](int val) { return val <= 0; });
    return it - nums.begin() + 1;
  }
};

int main() {
  {
    Solution sol;
    std::vector<int> test{3, 4, 45, 1};
    int expected = 2;
    int res = sol.firstMissingPositive(test);
    if (res != expected) {
      std::cout << "res = " << res << " expected = " << expected << '\n';
    }
  }
}
