#include <algorithm>
#include <iostream>
#include <sstream>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

bool IsPrime(int n) {
  for (int i = 2; i * i <= n; ++i) {
    if (!(n % i)) {
      return false;
    }
  }
  return true;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  if (IsPrime(n)) {
    std::cout << 1 << '\n';
  } else if (!(n % 2) || IsPrime(n - 2)) {
    std::cout << 2 << '\n';
  } else {
    std::cout << 3 << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(27
    )";
    Solution(ss);
    std::cout << "expected = 3\n";
  }
}
