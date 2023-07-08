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
  int a, b;
  input >> a >> b;

  int da = (a - 1) / 3;
  int db = (b - 1) / 3;
  if (da == db) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
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
