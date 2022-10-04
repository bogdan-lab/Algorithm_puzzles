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

uint64_t Mult(uint64_t l, uint64_t r, uint64_t m) { return (l * r) % m; }
uint64_t Diff(uint64_t l, uint64_t r) { return l < r ? r - l : l - r; }

void Solution(std::istream& input) {
  uint64_t n, m;
  input >> n >> m;
  std::vector<uint64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }

  if (m < n) {
    std::cout << "0\n";
    return;
  }

  uint64_t res = Diff(data[data.size() - 2], data.back()) % m;
  for (size_t i = 0; i < data.size() - 2; ++i) {
    for (size_t j = i + 1; j < data.size(); ++j) {
      res = Mult(res, Diff(data[i], data[j]), m);
    }
  }
  std::cout << res << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2 10
8 5
)";
    Solution(ss);
    std::cout << "expected = 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 12
1 4 5
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 7
1 4 9
)";
    Solution(ss);
    std::cout << "expected = 1\n";
  }
}
