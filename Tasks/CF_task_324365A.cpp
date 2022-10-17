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

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<int64_t> res(data.size() + 1);
  for (int i = 1; i < res.size(); ++i) {
    res[i] = res[i - 1] + data[i - 1];
  }

  for (const auto& el : res) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
