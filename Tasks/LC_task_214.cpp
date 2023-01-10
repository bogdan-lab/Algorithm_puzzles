#include <algorithm>
#include <string>
#include <string_view>

bool IsPalindrome(std::string_view str) {
  if (str.empty()) return true;
  int l = 0;
  int r = str.size() - 1;
  while (l < r) {
    if (str[l] != str[r]) return false;
    ++l;
    --r;
  }
  return true;
}

std::string BuildPalindrome(const std::string& s, int min_app) {
  std::string res;
  res.reserve(s.size() + min_app);
  res = s.substr(s.size() - min_app);
  std::reverse(res.begin(), res.end());
  return res + s;
}

class Solution {
 public:
  std::string shortestPalindrome(std::string s) {
    std::string_view sv = s;
    if (IsPalindrome(sv)) return std::string(sv);
    int min_app = sv.size() - 1;
    for (int i = sv.size() - 1; i > 0; --i) {
      if (IsPalindrome(sv.substr(0, i))) {
        min_app = sv.size() - i;
        break;
      }
    }
    return BuildPalindrome(s, min_app);
  }
};
