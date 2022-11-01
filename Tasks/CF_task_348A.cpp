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

bool AllSame(const std::vector<int64_t>& data) {
  int64_t v = data.front();
  for (int i = 1; i < data.size(); ++i) {
    if (data[i] != v) return false;
  }
  return true;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }
  if (AllSame(data)) {
    std::cout << data.front() + 1 << '\n';
    return;
  }
  std::nth_element(data.begin(), data.begin() + 1, data.end());
  int64_t init_count = *(data.begin() + 1);
  int64_t min_val = *std::min_element(data.begin(), data.end());
  int64_t max_val = *std::max_element(data.begin(), data.end());
  std::cout << init_count + std::max(max_val - init_count, min_val) << '\n';
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
