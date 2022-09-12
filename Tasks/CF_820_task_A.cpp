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
    int a, b, c;
    input >> a >> b >> c;
    int b_len = c < b ? b - 1 : 2 * c - b - 1;
    int a_len = a - 1;
    if (a_len < b_len) {
      std::cout << "1\n";
    } else if (a_len > b_len) {
      std::cout << "2\n";
    } else {
      std::cout << "3\n";
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
1 2 3
3 1 2
3 2 1
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
