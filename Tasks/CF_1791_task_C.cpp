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

void SolveOne(std::istream& input) {
  int n;
  std::string data;
  input >> n >> data;
  int l = 0;
  int r = static_cast<int>(data.size()) - 1;
  while (l < r && data[l] != data[r]) {
    ++l;
    --r;
  }
  std::cout << r - l + 1 << '\n';
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
