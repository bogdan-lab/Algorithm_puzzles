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

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    size_t mat, prog;
    input >> mat >> prog;
    size_t split_num = (mat + prog) / 4;
    std::cout << std::min({mat, prog, split_num}) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
5 5
10 1
2 3
0 0
17 2
1000000000 1000000000
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
