#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
int GetMinPossibleAnswer(const std::vector<int>& all_answers,
                         const std::vector<int>& pick_bin,
                         const std::vector<int>& match_bin);
bool CheckValidAnswer(int ans, const std::vector<int>& pick_bin,
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
  std::vector<int> all_answers(512);
  std::iota(all_answers.begin(), all_answers.end(), 0);
  std::cout << GetMinPossibleAnswer(all_answers, pick_bin, match_bin) << '\n';
}

int GetMinPossibleAnswer(const std::vector<int>& all_answers,
                         const std::vector<int>& pick_bin,
                         const std::vector<int>& match_bin) {
  for (const auto& el : all_answers) {
    if (CheckValidAnswer(el, pick_bin, match_bin)) {
      return el;
    }
  }
  assert(false);
}

bool CheckValidAnswer(int ans, const std::vector<int>& pick_bin,
                      const std::vector<int>& match_bin) {
  for (const auto& p : pick_bin) {
    bool found_pair = false;
    for (const auto& m : match_bin) {
      if ((ans | (m & p)) == ans) {
        found_pair = true;
        break;
      }
    }
    if (!found_pair) {
      return false;
    }
  }
  return true;
};

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
