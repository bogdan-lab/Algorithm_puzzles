#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class Solution {
 public:
  int firstMissingPositive(std::vector<int>& nums) {
    int size = nums.size();
    for (int i = 0; i < size; ++i) {
      while (nums[i] > 0 && nums[i] <= size && nums[i] - 1 != i) {
        int pos = nums[i] - 1;
        if (nums[pos] - 1 == pos) {
          break;
        } else {
          std::swap(nums[i], nums[pos]);
        }
      }
    }
    int i = 0;
    while (i < size && nums[i] == i + 1) {
      ++i;
    }
    return i + 1;
  }
};

int main() {
  {
    Solution sol;
    std::vector<int> test{3, 4, 2, 1};
    int expected = 5;
    int res = sol.firstMissingPositive(test);
    if (res != expected) {
      std::cout << "res = " << res << " expected = " << expected << '\n';
    }
  }
}
