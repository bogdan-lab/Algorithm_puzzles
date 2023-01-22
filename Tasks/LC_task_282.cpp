#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int64_t ToInt(char c) { return static_cast<int>(c) - static_cast<int>('0'); }

int64_t Apply(int64_t l, int64_t r, char op) {
  if (op == '+') return l + r;
  return l - r;
}

std::pair<int64_t, std::string_view> ParseValue(std::string_view str) {
  int64_t curr_val = ToInt(str.front());
  int64_t res = 1;
  int i = 1;
  while (i < str.size()) {
    if (str[i] == '*') {
      res *= curr_val;
      ++i;
      curr_val = ToInt(str[i]);
      ++i;
    } else if (str[i] == '-' || str[i] == '+') {
      break;
    } else {
      curr_val = 10 * curr_val + ToInt(str[i]);
      ++i;
    }
  }
  return {res * curr_val, str.substr(i)};
}

int64_t Calc(std::string_view str) {
  std::pair<int64_t, std::string_view> lhs = ParseValue(str);
  str = lhs.second;
  int64_t res = lhs.first;
  while (!str.empty()) {
    char sign = str.front();
    std::pair<int64_t, std::string_view> rhs = ParseValue(str.substr(1));
    res = Apply(res, rhs.first, sign);
    str = rhs.second;
  }
  return res;
}

void Merge(const std::string& num, const std::string& signs, std::string& out) {
  out.push_back(num.front());
  for (int i = 1; i < num.size(); ++i) {
    if (signs[i - 1] != 'X') {
      out.push_back(signs[i - 1]);
    }
    out.push_back(num[i]);
  }
}

class Solution {
 public:
  std::vector<std::string> addOperators(std::string num, int target) {
    std::vector<std::string> res;
    std::string curr_path;
    curr_path.reserve(2 * num.size() - 1);
    std::string signs;
    signs.reserve(num.size() - 1);
    for (int pluses = 0; pluses < num.size(); ++pluses) {
      for (int minuses = 0; minuses < num.size(); ++minuses) {
        for (int empty = 0; empty < num.size(); ++empty) {
          for (int mult = 0; mult < num.size(); ++mult) {
            if (mult + empty + pluses + minuses != num.size() - 1) {
              continue;
            }
            signs = std::string(mult, '*') + std::string(pluses, '+') +
                    std::string(minuses, '-') + std::string(empty, 'X');
            do {
              Merge(num, signs, curr_path);
              int64_t cp = Calc(curr_path);
              if (cp == target) {
                res.push_back(curr_path);
              }
              curr_path.clear();
            } while (std::next_permutation(signs.begin(), signs.end()));
            signs.clear();
          }
        }
      }
    }

    return res;
  }
};

int main() {
  {
    Solution s;
    std::vector<std::string> data = s.addOperators("2222222", 0);
    for (const auto& el : data) {
      std::cout << el << '\n';
    }
  }
  return 0;
}
