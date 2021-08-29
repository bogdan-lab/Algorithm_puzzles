#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
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
  size_t unused_open = 0;
  size_t unused_close = 0;
};

bool operator<(const Interval& lhs, const Interval& rhs) {
  return lhs.open < rhs.open || (lhs.open == rhs.open && lhs.close > rhs.close);
}

using BracketIntervals = std::set<Interval>;

size_t get_length(const BracketIntervals& vec);

BracketIntervals build_tree(const std::string& brackets);

Interval connect_intervals(const Interval& lhs, const Interval& rhs);

int main() {
   //run_tests();
  solve(std::cin);
  return 0;
}
Interval connect_intervals(const Interval& lhs, const Interval& rhs) {
  Interval res;
  res.open = lhs.open;
  res.close = rhs.close;
  size_t addition = std::min(lhs.unused_open, rhs.unused_close);
  res.len = lhs.len + rhs.len + 2 * addition;
  res.unused_open = lhs.unused_open + rhs.unused_open - addition;
  res.unused_close = lhs.unused_close + rhs.unused_close - addition;
  return res;
}

BracketIntervals build_tree(const std::string& brackets) {
  BracketIntervals res;
  std::queue<Interval> buff;
  for (size_t i = 0; i < brackets.size(); ++i) {
    Interval tmp;
    tmp.open = i;
    tmp.close = i + 1;
    tmp.unused_open = brackets[i] == '(';
    tmp.unused_close = brackets[i] == ')';
    buff.push(tmp);
  }
  std::queue<Interval> next_buff;
  while (true) {
      if(buff.empty()){
          buff.swap(next_buff);
      }
      if(buff.size()==1){
          buff.swap(next_buff);
          buff.push(next_buff.front());
          next_buff.pop();
      }
      if(buff.size()<=1) break;

    Interval lhs = buff.front();
    buff.pop();
    Interval rhs = buff.front();
    buff.pop();
    res.insert(lhs);
    res.insert(rhs);
    next_buff.push(connect_intervals(lhs, rhs));
  }
  res.insert(buff.front());
  return res;
}

size_t get_length(const std::vector<Interval>& scheme, size_t start,
                  size_t end) {
  if (end - start <= 1) return 0;
  Interval fnd;
  fnd.open = start;
  fnd.close = end;
  Interval res;
  res.open = start;
  auto it = std::lower_bound(scheme.begin(), scheme.end(), fnd);
  while (it != scheme.end() && it->open < end) {
    res = connect_intervals(res, *it);
    fnd.open = it->close;
    it = std::lower_bound(scheme.begin(), scheme.end(), fnd);
  }
  return res.len;
}

void solve(std::istream& input) {
  std::string brackets;
  input >> brackets;
  BracketIntervals scheme = build_tree(brackets);
  std::vector<Interval> vec(scheme.begin(), scheme.end());
  size_t m;
  input >> m;
  while (m--) {
    size_t s, e;
    input >> s >> e;
    std::cout << get_length(vec, s - 1, e) << '\n';
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

