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

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) {
    int64_t x, y;
    input >> x >> y;
    if (x > y) {
      std::cout << x + y << '\n';
    } else if (x == y) {
      std::cout << x << '\n';
    } else {
      int64_t p = y / x;
      p = p * x;
      std::cout << (y + p) / 2 << '\n';
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
