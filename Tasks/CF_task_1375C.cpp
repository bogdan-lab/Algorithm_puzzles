#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

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
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  if (data.front() < data.back()) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
3
1 2 3
4
3 1 2 4
3
2 3 1
6
2 4 6 1 3 5
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
