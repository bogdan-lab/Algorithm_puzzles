#include <algorithm>
#include <iostream>
#include <numeric>
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
  int64_t s = std::accumulate(data.begin(), data.end(), 0LL);
  int64_t max_val = *std::max_element(data.begin(), data.end());
  std::cout << std::max(max_val, (s + n - 2) / (n - 1)) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
3 2 2
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
2 2 2 2
)";
    Solution(ss);
    std::cout << "expected = 3\n";
  }
}
