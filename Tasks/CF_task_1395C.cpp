#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
int GetMinCollission(int val, const std::vector<int>& vec);
int ComposeMinVals(int pos_idx, const std::vector<int>& pick_bin,
                   const std::vector<int>& match_bin);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n = 0;
  int m = 0;
  input >> n >> m;
  std::vector<int> lhs(n);
  for (auto& el : lhs) {
    input >> el;
  }
  std::vector<int> rhs(m);
  for (auto& el : rhs) {
    input >> el;
  }
  std::vector<int> min_vals;
  min_vals.reserve(lhs.size());
  for (int i = 0; i < lhs.size(); ++i) {
    min_vals.push_back(ComposeMinVals(i, lhs, rhs));
  }
  int min_val = std::numeric_limits<int>::max();
  for (const auto& el : min_vals) {
    min_val = std::min(min_val, el);
  }
  std::cout << min_val << '\n';
}

int GetMinCollission(int val, const std::vector<int>& vec) {
  int min_val = val & vec.front();
  for (const auto& el : vec) {
    min_val = std::min(min_val, val & el);
  }
  return min_val;
}

int ComposeMinVals(int pos_idx, const std::vector<int>& pick_bin,
                   const std::vector<int>& match_bin) {
  int res = GetMinCollission(pick_bin[pos_idx], match_bin);
  for (const auto& el : pick_bin) {
    int min_change = std::numeric_limits<int>::max();
    for (const auto& collider : match_bin) {
      min_change = std::min(min_change, (res | (el & collider)) - res);
    }
    res += min_change;
  }
  return res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4 2
2 6 4 0
2 4
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(7 6
1 9 1 9 8 1 0
1 1 4 5 1 4
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(8 5
179 261 432 162 82 43 10 38
379 357 202 184 197
)";
    Solution(ss);
    std::cout << "expected = 147\n";
  }
}
