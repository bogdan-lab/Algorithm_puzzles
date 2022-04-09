
#include <string>
#include <string_view>

class Solution {
  void ConsumeStar(std::string_view s, std::string_view p, int& s_idx,
                   int& p_idx) {
    while (s_idx < s.size() && s[s_idx] == p[p_idx - 1]) {
      s_idx++;
    }
    p_idx++;
  }

  void ConsumeDotStar(std::string_view s, std::string_view p, int& s_idx,
                      int& p_idx) {
    p_idx += 2;
    if (p_idx == p.size()) {
      // match entire word
      s_idx = s.size();
      return;
    }
    // assume that after .* we have valid symbol
    // regex operates greadely -> search for the character match from the back
    size_t new_pos = s.find_last_of(p[p_idx]);
    if (new_pos == std::string_view::npos) {
      // p_idx points to valid char, do not move s_idx
      // at next cycle compare and understand that s[s_idx] != p[p_idx] ->
      // return false
      return;
    }
    s_idx = static_cast<int>(new_pos);
  }

 public:
  bool isMatch(std::string s, std::string p) {
    int s_idx = 0;
    int p_idx = 0;
    while (s_idx < s.size()) {
      if (s[s_idx] == p[p_idx]) {
        s_idx++;
        p_idx++;
      } else if (p[p_idx] == '*') {
        ConsumeStar(s, p, s_idx, p_idx);
      } else if (p[p_idx] == '.') {
        if (p_idx == p.size() - 1 || p[p_idx + 1] != '*') {
          s_idx++;
          p_idx++;
        } else {
          ConsumeDotStar(s, p, s_idx, p_idx);
        }
      } else {
        return false;
      }
    }
    // if we do not finish pattern it is bad
    return p_idx == p.size();
  }
};
