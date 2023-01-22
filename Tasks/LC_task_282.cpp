#include <algorithm>
#include <cctype>
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

void DFS(const std::string& str, int i, int64_t target, std::string& expr,
         std::vector<std::string>& res) {
  if (i == str.size() - 1) {
    if (target == Calc(expr)) {
      res.push_back(expr);
    }
    return;
  }

  for (const auto& el : {'*', '+', '-'}) {
    expr.push_back(el);
    expr.push_back(str[i + 1]);
    DFS(str, i + 1, target, expr, res);
    expr.pop_back();
    expr.pop_back();
  }

  bool prev_empty = expr.size() >= 2 && std::isdigit(expr[expr.size() - 2]);
  bool curr_allow = expr.back() != '0';
  if (prev_empty || curr_allow) {
    expr.push_back(str[i + 1]);
    DFS(str, i + 1, target, expr, res);
    expr.pop_back();
  }
}

class Solution {
 public:
  std::vector<std::string> addOperators(std::string num, int target) {
    std::vector<std::string> res;
    std::string expression;
    expression.reserve(2 * num.size() - 1);
    expression.push_back(num.front());
    DFS(num, 0, target, expression, res);

    return res;
  }
};

int main() {
  {
    Solution s;
    std::vector<std::string> data = s.addOperators("1000000009", 9);
    for (const auto& el : data) {
      std::cout << el << '\n';
    }
  }
  return 0;
}
