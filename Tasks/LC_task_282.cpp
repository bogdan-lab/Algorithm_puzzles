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

struct Node {
  int64_t res = 0;
  char op = '+';
  int64_t m = 1;
  int64_t c = 0;
};

int64_t Eval(const Node& n) { return Apply(n.res, n.m * n.c, n.op); }

Node SetOperation(const Node& n, char new_op, int val) {
  Node r;
  r.res = Eval(n);
  r.op = new_op;
  r.c = val;
  return r;
}

Node UpdateMultiply(const Node& n, int val) {
  Node r = n;
  r.m *= r.c;
  r.c = val;
  return r;
}

Node UpdateMultiDigit(const Node& n, int val) {
  Node r = n;
  r.c = 10 * r.c + val;
  return r;
}

void DFS(const Node& curr_node, const std::string& str, int i, int64_t target,
         std::string& expr, std::vector<std::string>& res) {
  if (i == str.size() - 1) {
    if (target == Eval(curr_node)) {
      res.push_back(expr);
    }
    return;
  }

  for (const auto& el : {'*', '+', '-'}) {
    expr.push_back(el);
    expr.push_back(str[i + 1]);
    int val = ToInt(str[i + 1]);
    if (el == '*') {
      DFS(UpdateMultiply(curr_node, val), str, i + 1, target, expr, res);
    } else {
      DFS(SetOperation(curr_node, el, val), str, i + 1, target, expr, res);
    }
    expr.pop_back();
    expr.pop_back();
  }

  bool prev_empty = expr.size() >= 2 && std::isdigit(expr[expr.size() - 2]);
  bool curr_allow = expr.back() != '0';
  if (prev_empty || curr_allow) {
    expr.push_back(str[i + 1]);
    DFS(UpdateMultiDigit(curr_node, ToInt(str[i + 1])), str, i + 1, target,
        expr, res);
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
    Node node;
    node.c = ToInt(num.front());
    DFS(node, num, 0, target, expression, res);

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
