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
  int n, k;
  input >> n >> k;
  std::vector<std::string> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::sort(data.begin(), data.begin() + k);
  for (int i = 0; i < k; ++i) {
    std::cout << data[i] << '\n';
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
