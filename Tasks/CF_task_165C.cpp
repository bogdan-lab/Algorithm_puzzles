#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::pair<int, uint64_t> CountZeros(const std::string& str, int i) {
  uint64_t count = 0;
  while (i < str.size() && str[i] == '0') {
    ++count;
    ++i;
  }
  return {i, count};
}

uint64_t Calc(uint64_t l, uint64_t r) { return l + r + l * r + 1; }

void SolveZero(const std::string& str) {
  uint64_t total = 0;
  uint64_t count = 0;
  int streak = 0;
  for (const auto& el : str) {
    if (el == '0') {
      ++streak;
      count += streak;
    } else {
      total += count;
      count = 0;
      streak = 0;
    }
  }
  std::cout << total + count << '\n';
}

void Solution(std::istream& input) {
  int k;
  std::string str;
  input >> k >> str;

  if (k == 0) {
    SolveZero(str);
    return;
  }

  int li = 0;
  int ri = 0;
  int one_count = 0;
  while (ri < str.size() && one_count < k) {
    if (str[ri] == '1') {
      ++one_count;
    }
    ++ri;
  }
  if (one_count < k) {
    std::cout << "0\n";
    return;
  }

  std::pair<int, uint64_t> left = CountZeros(str, li);
  std::pair<int, uint64_t> right = CountZeros(str, ri);

  uint64_t count = Calc(left.second, right.second);
  while (right.first < str.size()) {
    ++left.first;
    ++right.first;
    left = CountZeros(str, left.first);
    right = CountZeros(str, right.first);
    count += Calc(left.second, right.second);
  }
  std::cout << count << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(0
01010
)";
    Solution(ss);
    std::cout << "expected = 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
01010
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(100
01010
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}

// S = left + right + left*right + 1
// 00100
// 1
// 01
// 001
// 10
// 100
// 010
// 0100
// 0010
// 00100
// S = 2 + 2 + 4 + 1 = 9
//
// 0100
// 1
// 01
// 10
// 100
// 010
// 0100
// S = 1 + 2 + 1*2 + 1 = 6
//
// 1 -> 1
// 2 -> 3
// 3 -> 6
//
// 000
// 0
//  0
// 00
//   0
//  00
// 000
