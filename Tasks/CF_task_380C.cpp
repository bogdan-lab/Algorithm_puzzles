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

struct Request {
  size_t num = 0;
  size_t start = 0;
  size_t end = 0;
};

bool operator<(const Request& lhs, const Request& rhs) {
  size_t lhs_len = lhs.end - lhs.start;
  size_t rhs_len = rhs.end - rhs.start;
  return lhs_len < rhs_len;
}

std::vector<size_t> calc_answers(const std::vector<Request>& requests,
                                 const std::string& brackets);

Interval connect_intervals(const Interval& lhs, const Interval& rhs);

Interval get_interval(const BracketIntervals& scheme, size_t start, size_t end);

BracketIntervals get_one_sized_intervals(const std::string& brackets);

int main() {
  // run_tests();
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

BracketIntervals get_one_sized_intervals(const std::string& brackets) {
  BracketIntervals res;
  for (size_t i = 0; i < brackets.size(); ++i) {
    res.insert({.open = i,
                .close = i + 1,
                .len = 0,
                .unused_open = (brackets[i] == '(' ? 1u : 0u),
                .unused_close = (brackets[i] == ')' ? 1u : 0u)});
  }
  return res;
}
Interval get_interval(const BracketIntervals& scheme, size_t start,
                      size_t end) {
  Interval fnd;
  fnd.open = start;
  fnd.close = end;
  Interval res;
  res.open = start;
  auto it = scheme.lower_bound(fnd);
  while (it != scheme.end() && it->open < end) {
    res = connect_intervals(res, *it);
    fnd.open = it->close;
    it = scheme.lower_bound(fnd);
  }
  return res;
}

std::vector<size_t> calc_answers(const std::vector<Request>& requests,
                                 const std::string& brackets) {
  std::vector<size_t> res(requests.size());
  BracketIntervals scheme = get_one_sized_intervals(brackets);
  for (const auto& rq : requests) {
    Interval rq_int = get_interval(scheme, rq.start, rq.end);
    res[rq.num] = rq_int.len;
    scheme.insert(rq_int);
  }
  return res;
}

void solve(std::istream& input) {
  std::string brackets;
  input >> brackets;
  size_t m;
  input >> m;
  std::vector<Request> requests;
  size_t idx = 0;
  while (m--) {
    size_t s, e;
    input >> s >> e;
    requests.push_back({.num = idx++, .start = s - 1, .end = e});
  }
  std::sort(requests.begin(), requests.end());
  std::vector<size_t> answers = calc_answers(requests, brackets);
  for (auto el : answers) {
    std::cout << el << '\n';
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

