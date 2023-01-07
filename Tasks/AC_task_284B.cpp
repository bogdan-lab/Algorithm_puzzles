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
  int n;
  input >> n;

  int count = 0;
  while (n--) {
    int val;
    input >> val;
    count += val & 1;
  }
  std::cout << count << '\n';
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
3
1 2 3
2
20 23
10
6 10 4 1 5 9 8 6 5 1
1
1000000000
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
