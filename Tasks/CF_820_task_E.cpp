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
  int t = 50;
  int i = 1;
  int j = 2;
  while (t--) {
    std::cout << "? " << i << ' ' << j << std::endl;
    int64_t a;
    input >> a;
    if (a == -1) {
      std::cout << "! " << j - 1 << '\n';
      break;
    }
    std::cout << "? " << j << ' ' << i << std::endl;
    int64_t b;
    input >> b;
    if (a != b) {
      std::cout << "! " << a + b << '\n';
      break;
    }
    ++j;
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
