#include <algorithm>
#include <cassert>
#include <string>

bool Check(std::string& src, const std::string& dst, int start, int end) {
  if (start == end || start >= src.size()) return true;
  for (int j = start; j < end; ++j) {
    if (src[j] == dst[start]) {
      std::rotate(src.begin() + start, src.begin() + j, src.begin() + j + 1);
      if (Check(src, dst, start + 1, j + 1) && Check(src, dst, j + 1, end)) {
        return true;
      } else {
        // Restore
        std::rotate(src.begin() + start, src.begin() + start + 1,
                    src.begin() + j + 1);
      }
    }
  }
  return false;
}

class Solution {
 public:
  bool isScramble(std::string s1, std::string s2) {
    return Check(s1, s2, 0, s1.size());
  }
};

int main() {
  Solution s;
  assert(!s.isScramble("abcde", "caebd"));
  assert(s.isScramble("abcdbdacbdac", "bdacabcdbdac"));
  return 0;
}
