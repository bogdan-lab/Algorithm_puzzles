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

void PrintAnswer(int n) {
  if (n == 3) {
    std::cout << "-1\n";
    return;
  }
  if (n % 2) {
    std::cout << n-- << ' ';
    std::cout << n-- << ' ';
    for (int i = 1; i <= n; ++i) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
    return;
  }
  for (int i = n; i > 0; --i) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    PrintAnswer(n);
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
4
3
7
5
2
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
