#include <algorithm>

class Solution {
 public:
  int countDigitOne(int n) {
    int ans = 0;

    for (int64_t p = 1; p <= n; p *= 10) {
      int div = p * 10;
      int c = n / div;
      int r = n - c * div;
      if (c > 0) {
        ans += c * p;
      }
      if (r >= p) {
        ans += std::min(r - p + 1, p);
      }
    }

    return ans;
  }
};
