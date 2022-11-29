#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

class Solution {
 public:
  int candy(std::vector<int>& ratings) {
    std::vector<int> candies(ratings.size());
    int i = 0;
    while (true) {
      // process increase
      while (i < ratings.size() - 1 && ratings[i] < ratings[i + 1]) {
        candies[i + 1] = candies[i] + 1;
        ++i;
      }
      if (i == ratings.size() - 1) {
        break;
      }
      // process equal
      while (i < ratings.size() - 1 && ratings[i] == ratings[i + 1]) {
        ++i;
      }
      if (i == ratings.size() - 1) {
        break;
      }
      // process decrease
      int decrease_start = i;
      while (i < ratings.size() - 1 && ratings[i] > ratings[i + 1]) {
        ++i;
      }
      int decrease_end = i;
      if (decrease_start < decrease_end) {
        int j = decrease_end - 1;
        while (decrease_start <= j) {
          candies[j] = std::max(candies[j], candies[j + 1] + 1);
          --j;
        }
      }
    }

    int count = ratings.size();
    for (const auto& el : candies) {
      count += el;
    }
    return count;
  }
};

int main() {
  Solution s;
  {
    std::vector<int> test{1, 2, 87, 87, 87, 2, 1};
    assert(s.candy(test) == 13);
  }
  return 0;
}
