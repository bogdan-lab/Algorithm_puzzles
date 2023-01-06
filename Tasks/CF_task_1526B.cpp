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
  int x;
  input >> x;

  int val = x;
  while (val % 11) {
    --val;
  }
  int n = x - val;
  int k = val / 11;

  if (k / 10 >= n) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
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
    ss << R"(4
2047
144
69
10
)";
    Solution(ss);
    std::cout << "expected = YES; YES; NO; NO\n";
  }
}
