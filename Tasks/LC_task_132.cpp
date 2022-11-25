#include <algorithm>
#include <string>
#include <string_view>

bool IsPalindrome(std::string_view str) {
  for (int i = 0; i < str.size() / 2; ++i) {
    if (str[i] != str[str.size() - i - 1]) {
      return false;
    }
  }
  return true;
}

int CalcCuts(std::string_view buff) {
  int count = 0;
  int si = 0;
  while (si < buff.size()) {
    int end = buff.size();
    while (end > si) {
      if (IsPalindrome(buff.substr(si, end - si))) {
        break;
      }
      --end;
    }
    si = end;
    ++count;
  }
  return count - 1;
}

class Solution {
 public:
  int minCut(std::string s) {
    int l = CalcCuts(s);
    std::reverse(s.begin(), s.end());
    return std::min(l, CalcCuts(s));
  }
};
