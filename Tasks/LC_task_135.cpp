#include <algorithm>
#include <cassert>
#include <limits>
#include <stack>
#include <vector>

class Solution {
 public:
  int candy(std::vector<int>& ratings) {
    std::vector<int> candies(ratings.size());
    int i = 0;
    std::stack<int> buff;
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
      while (i < ratings.size() - 1 && ratings[i] > ratings[i + 1]) {
        buff.push(i);
        ++i;
      }
      int prev = i;
      while (!buff.empty()) {
        int j = buff.top();
        buff.pop();
        candies[j] = std::max(candies[j], candies[prev] + 1);
        prev = j;
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
