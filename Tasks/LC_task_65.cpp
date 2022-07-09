#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>

bool IsInteger(const std::string& str, size_t begin, size_t end,
               bool allow_empty, bool allow_sign);

bool IsDecimal(const std::string& str, size_t begin, size_t end);

class Solution {
 public:
  bool isNumber(std::string s) {
    size_t e_pos = [&s]() {
      size_t res = s.find('e');
      if (res == std::string::npos) {
        res = s.find('E');
      }
      return res;
    }();

    if (e_pos == std::string::npos) {
      return IsDecimal(s, 0, s.size()) ||
             IsInteger(s, 0, s.size(), /*allow_empty=*/false,
                       /*allow_sign=*/true);
    } else {
      return IsDecimal(s, 0, e_pos) &&
             IsInteger(s, e_pos + 1, s.size(), /*allow_empty=*/false,
                       /*allow_sign=*/true);
    }
  }
};

bool IsDecimal(const std::string& str, size_t begin, size_t end) {
  if (begin == end) return false;
  auto it_begin = str.begin() + begin;
  auto it_end = it_begin + end;
  if (std::none_of(it_begin, it_end,
                   [](char ch) { return std::isdigit(ch); })) {
    return false;
  }
  auto it = std::find(it_begin, it_end, '.');
  if (it == it_end) {
    return IsInteger(str, begin, end, /*allow_empty=*/false,
                     /*allow_sign=*/true);
  } else {
    size_t dot_pos = it - str.begin();
    return IsInteger(str, begin, dot_pos, /*allow_empty=*/true,
                     /*allow_sign=*/true) &&
           IsInteger(str, dot_pos + 1, end, /*allow_empty=*/true,
                     /*allow_sign=*/false);
  }
}

bool IsInteger(const std::string& str, size_t begin, size_t end,
               bool allow_empty, bool allow_sign) {
  if (begin == end) return allow_empty;
  if (str[begin] == '+' || str[begin] == '-') {
    if (!allow_sign) return false;
    ++begin;
    if (begin == end) return allow_empty;
  }
  return std::all_of(str.begin() + begin, str.begin() + end,
                     [](char ch) { return std::isdigit(ch); });
}

int main() {
  Solution s;
  assert(s.isNumber(".1"));
  assert(s.isNumber("+.1"));
  assert(s.isNumber("+1.1"));
  assert(s.isNumber("+1."));
  assert(s.isNumber("+1.e5"));
  assert(s.isNumber("+1.e-5"));
  assert(s.isNumber("1.e+5"));
  assert(s.isNumber("-1.e+5"));

  assert(!s.isNumber("-"));
  assert(!s.isNumber("-."));
  assert(!s.isNumber("."));
  assert(!s.isNumber("+-."));
  assert(!s.isNumber(".+1"));
  assert(!s.isNumber("e3"));
  assert(!s.isNumber("1e"));
  assert(!s.isNumber("--6"));
  assert(!s.isNumber("-+3."));
  assert(!s.isNumber("99e2.5"));

  return 0;
}