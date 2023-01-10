#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

std::string BuildPalindrome(const std::string& s, int min_app) {
  std::string res;
  res.reserve(s.size() + min_app);
  res = s.substr(s.size() - min_app);
  std::reverse(res.begin(), res.end());
  return res + s;
}

int CountEqual(const std::string& s, int l, int r) {
  int count = 0;
  for (int i = l, j = r; j < s.size(); ++i, ++j) {
    if (s[i] != s[j]) break;
    ++count;
  }
  return count;
}

std::vector<int> BuildZArray(const std::string& s) {
  std::vector<int> z(s.size());
  z[0] = -1;

  int l = 0;
  int r = 0;

  for (int i = 1; i < s.size(); ++i) {
    if (i > l && i < r) {
      int ppos = i - l;
      if (z[ppos] + i < r) {
        z[i] = z[ppos];
      } else {
        int known = r - i;
        int eqc = CountEqual(s, known, r);
        z[i] = known + eqc;
        l = i;
        r = l + z[i];
      }
    } else {
      int eqc = CountEqual(s, 0, i);
      l = i;
      r = l + eqc;
      z[i] = eqc;
    }
  }

  return z;
}

int GetPalindromLength(const std::vector<int>& z, int word_size,
                       bool is_even_word) {
  int count = word_size / 2;
  int ridx = count;
  bool char_in_center = false;
  if (!is_even_word) {
    char_in_center = true;
    ridx = count + 1;
  }
  while (count > 0) {
    if (z[ridx] >= count) break;
    if (char_in_center) {
      char_in_center = false;
    } else {
      char_in_center = true;
      --count;
    }
    ++ridx;
  }
  return 2 * count + (char_in_center ? 1 : 0);
}

class Solution {
 public:
  std::string shortestPalindrome(std::string s) {
    if (s.empty()) return {};
    if (s.size() == 1) return s;
    std::string data;
    data.reserve(s.size() + (s.size() + 1) / 2);
    data = s;
    std::reverse(data.begin(), data.end());
    data = s.substr(0, (s.size() + 1) / 2) + data;

    std::vector<int> z = BuildZArray(data);
    int len = GetPalindromLength(z, s.size(), !(s.size() % 2));
    return BuildPalindrome(s, s.size() - len);
  }
};

int main() {
  Solution s;
  assert(s.shortestPalindrome("aba") == "aba");
  assert(s.shortestPalindrome("aacecaaa") == "aaacecaaa");
  return 0;
}
