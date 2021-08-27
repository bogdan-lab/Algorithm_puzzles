#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

void solve(std::istream& input = std::cin);
void run_tests();

struct Interval {
  size_t open = 0;
  size_t close = 0;
  size_t len = 0;
};

bool operator<(const Interval& lhs, const Interval& rhs) {
  return lhs.open < rhs.open || (lhs.open == rhs.open && lhs.close > rhs.close);
}

using BracketIntervals = std::set<Interval>;

BracketIntervals get_intervals(const std::string& brackets);
size_t get_length(BracketIntervals& vec);

int main() {
   //run_tests();
  solve(std::cin);
  return 0;
}

BracketIntervals get_intervals(const std::string& brackets) {
  BracketIntervals res;
  std::stack<size_t> open;
  for (size_t i = 0; i < brackets.size(); ++i) {
    switch (brackets[i]) {
      case '(': {
        open.push(i);
        break;
      }
      case ')': {
        if (!open.empty()) {
          res.insert({open.top(), i, i - open.top() + 1});
          open.pop();
        }
        break;
      }
    }
  }
  return res;
}

size_t get_length(BracketIntervals& scheme, size_t start, size_t end) {
  Interval fnd{start, end, 0};
  size_t res = 0;
  auto it = scheme.lower_bound(fnd);
  bool is_safe_to_cache = true;
  while (it != scheme.end() && it->open <= end) {
    if (it->close <= end) {
      res += it->len;
      auto nxt = scheme.upper_bound({it->close, end, 0});
      is_safe_to_cache = nxt!=scheme.end() &&  nxt->open - it->close == 1;
      it = nxt;
    } else {
      ++it;
      is_safe_to_cache = false;
    }
  }
  if (res && is_safe_to_cache) {
    scheme.insert({start, end, res});
  }
  return res;
}

void solve(std::istream& input) {
  std::string brackets;
  input >> brackets;
  BracketIntervals scheme = get_intervals(brackets);
  size_t m;
  input >> m;
  while (m--) {
    size_t s, e;
    input >> s >> e;
    std::cout << get_length(scheme, s - 1, e - 1) << '\n';
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10
)";
    solve(ss);
    std::cout << "expected = 0 0 2 10 4 6 6\n";
  }
  {
    std::stringstream ss;
    ss << R"((
1
1 1
)";
    solve(ss);
    std::cout << "expected = 0\n";
  }
}

