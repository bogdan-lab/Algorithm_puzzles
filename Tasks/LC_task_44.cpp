#include <string>
#include <vector>

constexpr int kEmptyValue = 2;

bool Match(const std::string& str, const std::string& ptrn, size_t str_pos,
           size_t ptrn_pos, std::vector<std::vector<int>>& memo);

class Solution {
 public:
  bool isMatch(std::string s, std::string p) {
    std::vector<std::vector<int>> memo(s.size());
    for (auto& el : memo) {
      el.resize(p.size(), kEmptyValue);
    }
    return Match(s, p, 0, 0, memo);
  }
};

bool Match(const std::string& str, const std::string& ptrn, size_t str_pos,
           size_t ptrn_pos, std::vector<std::vector<int>>& memo) {
  if (str_pos == str.size() && ptrn_pos == ptrn.size()) {
    return true;
  }
  if (str_pos == str.size()) {
    auto pos = ptrn.find_first_not_of('*', ptrn_pos);
    return pos == std::string::npos;
  }
  if (str_pos >= str.size() || ptrn_pos >= ptrn.size()) {
    return false;
  }
  if (memo[str_pos][ptrn_pos] == kEmptyValue) {
    if (ptrn[ptrn_pos] == str[str_pos] || ptrn[ptrn_pos] == '?') {
      memo[str_pos][ptrn_pos] =
          Match(str, ptrn, str_pos + 1, ptrn_pos + 1, memo) ? 1 : 0;
    } else if (ptrn[ptrn_pos] == '*') {
      memo[str_pos][ptrn_pos] =
          Match(str, ptrn, str_pos + 1, ptrn_pos + 1, memo) ||
                  Match(str, ptrn, str_pos + 1, ptrn_pos, memo) ||
                  Match(str, ptrn, str_pos, ptrn_pos + 1, memo)
              ? 1
              : 0;
    } else {
      memo[str_pos][ptrn_pos] = 0;
    }
  }
  return memo[str_pos][ptrn_pos];
}

