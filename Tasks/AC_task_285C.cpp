#include <iostream>
#include <sstream>
#include <string>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int64_t ToInt(char c) {
  return static_cast<int>(c) - static_cast<int>('A') + 1;
}

void Solution(std::istream& input) {
  std::string data;
  input >> data;

  int64_t power = 1;
  int64_t val = ToInt('Z');

  int64_t index = 0;
  for (auto it = data.rbegin(); it != data.rend(); ++it) {
    index += power * ToInt(*it);
    power *= val;
  }

  std::cout << index << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
