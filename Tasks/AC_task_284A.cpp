#include <iostream>
#include <sstream>
#include <string>
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

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<std::string> data(n);
  for (auto& el : data) input >> el;

  for (auto it = data.rbegin(); it != data.rend(); ++it) {
    std::cout << *it << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
2023
Year
New
Happy
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
