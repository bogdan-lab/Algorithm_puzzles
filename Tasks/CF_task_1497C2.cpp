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

void SolveOne(std::istream& input) {
  int n, k;
  input >> n >> k;
  while (k > 3) {
    std::cout << "1 ";
    --k;
    --n;
  }
  if (n & 1) {
    std::cout << "1 ";
    --n;
    n /= 2;
    std::cout << n << " " << n << '\n';
  } else {
    if (n % 4) {
      n -= 2;
      n /= 2;
      std::cout << 2 << " " << n << " " << n << '\n';
    } else {
      int val = n / 4;
      std::cout << val << " " << val << " " << 2 * val << '\n';
    }
  }
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
