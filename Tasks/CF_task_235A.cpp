#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
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

void Solution(std::istream& input) {
  uint64_t n;
  input >> n;
  if (n <= 2) {
    std::cout << n << '\n';
    return;
  }
  if (n % 2) {
    std::cout << n * (n - 1) * (n - 2) << '\n';
  } else {
    if (n % 3) {
      std::cout << n * (n - 1) * (n - 3) << '\n';
    } else {
      std::cout << (n - 1) * (n - 2) * (n - 3) << '\n';
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(9)";
    Solution(ss);
    std::cout << "expected = 504\n";
  }
  {
    std::stringstream ss;
    ss << R"(7)";
    Solution(ss);
    std::cout << "expected = 210\n";
  }
  {
    std::stringstream ss;
    ss << R"(1)";
    Solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(21)";
    Solution(ss);
    std::cout << "expected = 7980\n";
  }
}
