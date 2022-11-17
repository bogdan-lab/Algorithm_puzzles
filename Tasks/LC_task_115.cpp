#include <cassert>
#include <string>
#include <vector>

class Solution {
 public:
  int numDistinct(std::string s, std::string t) {
    std::vector<uint64_t> prev_layer(s.size());
    std::vector<uint64_t> curr_layer(s.size());

    prev_layer.back() = (s.back() == t.back());

    if (s.size() == 1) {
      if (t.size() > 1) {
        return 0;
      }
      return prev_layer.back();
    }

    for (int j = s.size() - 2; j >= 0; --j) {
      prev_layer[j] = prev_layer[j + 1] + (s[j] == t.back());
    }

    if (t.size() == 1) {
      return prev_layer[0];
    }

    for (int i = t.size() - 2; i >= 0; --i) {
      int start = s.size() - 1;
      while (start >= 0 && prev_layer[start] == 0) {
        curr_layer[start] = 0;
        --start;
      }
      --start;
      if (start < 0) {
        return 0;
      }
      curr_layer[start + 1] = 0;
      for (int j = start; j >= 0; --j) {
        curr_layer[j] = curr_layer[j + 1] + prev_layer[j + 1] * (t[i] == s[j]);
      }
      std::swap(prev_layer, curr_layer);
    }
    return prev_layer[0];
  }
};

int main() {
  Solution s;
  assert(s.numDistinct("rabbbit", "rabbit") == 3);
  assert(s.numDistinct("babgbag", "bag") == 5);
  return 0;
}
