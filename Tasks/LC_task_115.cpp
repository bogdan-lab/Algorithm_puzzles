#include <cassert>
#include <string>
#include <vector>

class Solution {
 public:
  int numDistinct(std::string s, std::string t) {
    std::vector<std::vector<uint64_t>> data(t.size(),
                                            std::vector<uint64_t>(s.size()));

    for (int j = s.size() - 1; j >= 0; --j) {
      if (j + 1 < s.size()) {
        data[t.size() - 1][j] = data[t.size() - 1][j + 1] + (s[j] == t.back());
      } else {
        data[t.size() - 1][j] = (s[j] == t.back());
      }
    }
    if (t.size() == 1) {
      return data[0][0];
    }
    for (int i = t.size() - 2; i >= 0; --i) {
      int start = s.size() - 1;
      while (start >= 0 && data[i + 1][start] == 0) {
        --start;
      }
      --start;
      if (start < 0) {
        return 0;
      }
      for (int j = start; j >= 0; --j) {
        if (t[i] == s[j]) {
          data[i][j] = data[i][j + 1] + data[i + 1][j + 1];
        } else {
          data[i][j] = data[i][j + 1];
        }
      }
    }
    return data[0][0];
  }
};

int main() {
  Solution s;
  assert(s.numDistinct("rabbbit", "rabbit") == 3);
  assert(s.numDistinct("babgbag", "bag") == 5);
  return 0;
}
