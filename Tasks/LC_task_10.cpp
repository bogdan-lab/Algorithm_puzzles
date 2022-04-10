
#include <string>
#include <string_view>

class Solution {
  bool ConsumeDotStar(std::string_view s, std::string_view p, int& s_idx,
                      int& p_idx) {
    p_idx += 2;
    if (p_idx == p.size()) {
      // match entire word
      s_idx = s.size();
      return true;
    }
    // assume that after .* we have valid symbol
    // regex operates greadely -> search for the character match from the back
    size_t new_pos = s.find_last_of(p[p_idx]);
    if (new_pos == std::string_view::npos || s_idx > new_pos) {
      return false;
    }
    s_idx = static_cast<int>(new_pos);
    return true;
  }

  bool NextNotStar(std::string_view p, int p_idx) {
    return p_idx == p.size() - 1 || p[p_idx + 1] != '*';
  }

  bool ConsumeCharStar(std::string_view s, std::string_view p, int& s_idx,
                       int& p_idx) {
    const char mc = p[p_idx];
    const int s_init_idx = s_idx;
    p_idx += 2;
    while (s_idx < s.size() && s[s_idx] == mc) {
      s_idx++;
    }
    int tmp_idx = s_idx;
    while (p_idx < p.size() && p[p_idx] == mc) {
      if (tmp_idx < s_init_idx) {
        return false;
      }
      tmp_idx--;
      p_idx++;
    }
    return true;
  }

  bool ConsumeChar(std::string_view s, std::string_view p, int& s_idx,
                   int& p_idx) {
    if (s[s_idx] != p[p_idx]) return false;
    s_idx++;
    p_idx++;
    return true;
  }

 public:
  bool isMatch(std::string s, std::string p) {
    int s_idx = 0;
    int p_idx = 0;
    bool not_failed = true;
    while (not_failed && s_idx < s.size() && p_idx < p.size()) {
      if (p[p_idx] == '.') {
        if (NextNotStar(p, p_idx)) {
          s_idx++;
          p_idx++;
        } else {
          // .* case
          not_failed = ConsumeDotStar(s, p, s_idx, p_idx);
        }
      } else {
        // p[p_idx] valid character
        if (NextNotStar(p, p_idx)) {
          not_failed = ConsumeChar(s, p, s_idx, p_idx);
        } else {
          // case with [c]*, where c = p[p_idx]
          not_failed = ConsumeCharStar(s, p, s_idx, p_idx);
        }
      }
    }
    // if we need we can throw away zero characters in the end of the pattern
    if (p_idx == p.size() - 2 && p.back() == '*') {
      p_idx = p.size();
    }
    return not_failed && p_idx == p.size() && s_idx == s.size();
  }
};
