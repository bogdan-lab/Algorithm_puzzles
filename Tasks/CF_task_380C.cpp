#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

void solve(std::istream& input = std::cin);
void run_tests();

using BracketIntervals = std::map<size_t, size_t>;  // open -> close

BracketIntervals get_intervals(const std::string& brackets);
size_t get_length(const BracketIntervals& vec);

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
          res[open.top()] = i;
          open.pop();
        }
        break;
      }
    }
  }
  return res;
}

size_t get_length(const BracketIntervals& scheme, size_t start, size_t end) {
  auto start_it = scheme.lower_bound(start);
  auto end_it = scheme.upper_bound(end);
  size_t res = 0;
  for (auto it = start_it; it != end_it; ++it) {
    if (it->second <= end) res += 2;
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

