#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

size_t GetMaxElixirNumber(const std::vector<int64_t>& data, size_t pos,
                          int64_t health);

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
  std::cout << GetMaxElixirNumber(data, /*pos=*/0, /*health=*/0) << '\n';
}

size_t GetMaxElixirNumber(const std::vector<int64_t>& data, size_t pos,
                          int64_t health) {
  if (pos == data.size()) {
    return 0;
  }
  if (health + data[pos] >= 0) {
    return std::max(1 + GetMaxElixirNumber(data, pos + 1, health + data[pos]),
                    GetMaxElixirNumber(data, pos + 1, health));
  }
  return GetMaxElixirNumber(data, pos + 1, health);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
4 -4 1 -3 1 -3
)";
    Solution(ss);
    std::cout << "expected = 5\n";
  }
}
