#include <algorithm>
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
  std::vector<std::string> data{"ACE", "BDF", "CEG", "DFA",
                                "EGB", "FAC", "GBD"};

  std::string word;
  input >> word;

  auto it = std::find(data.begin(), data.end(), word);
  if (it == data.end()) {
    std::cout << "No\n";
  } else {
    std::cout << "Yes\n";
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
