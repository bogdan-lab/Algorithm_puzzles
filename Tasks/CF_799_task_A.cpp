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
  int t;
  input >> t;
  while (t--) {
    int a, b, c, d;
    input >> a >> b >> c >> d;
    size_t count = (b > a) + (c > a) + (d > a);
    std::cout << count << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
2 3 4 1
10000 0 1 2
500 600 400 300
0 9999 10000 9998
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
