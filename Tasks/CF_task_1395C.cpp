#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
int UpdateMinVal(int curr_min_val, int val, const std::vector<int>& match_bin);
int GetBestFor(int index, const std::vector<int>& pick_bin,
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
  std::vector<int> pick_bin(n);
  for (auto& el : pick_bin) {
    input >> el;
  }
  std::vector<int> match_bin(m);
  for (auto& el : match_bin) {
    input >> el;
  }

  std::vector<int> min_vals;
  min_vals.reserve(pick_bin.size());
  for (int i = 0; i < pick_bin.size(); ++i) {
    min_vals.push_back(GetBestFor(i, pick_bin, match_bin));
  }
  std::cout << *std::min_element(min_vals.begin(), min_vals.end()) << '\n';
}

void Print(const std::vector<int>& data) {
  for (const auto& el : data) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

int GetBestFor(int index, const std::vector<int>& pick_bin,
               const std::vector<int>& match_bin) {
  std::vector<int> result;
  result.reserve(match_bin.size());
  for (const auto& el : match_bin) {
    result.push_back((pick_bin[index] & el));
  }
  for (const auto& el : pick_bin) {
    for (auto& res_el : result) {
      res_el = UpdateMinVal(res_el, el, match_bin);
    }
  }
  return *std::min_element(result.begin(), result.end());
}

int UpdateMinVal(int curr_min_val, int val, const std::vector<int>& match_bin) {
  int min_change = std::numeric_limits<int>::max();
  for (const auto& el : match_bin) {
    min_change =
        std::min(min_change, (curr_min_val | (el & val)) - curr_min_val);
  }
  return curr_min_val + min_change;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(19 16
272 140 389 278 27 131 328 422 153 414 222 507 405 445 200 243 403 82 317
447 73 189 396 72 494 492 386 203 226 389 482 311 500 344 360
)";
    Solution(ss);
    std::cout << "expected = 72\n";
  }
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
