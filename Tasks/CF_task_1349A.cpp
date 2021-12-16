#include <array>
#include <iostream>
#include <sstream>
#include <vector>

constexpr size_t kMaxSize = 100'000;

void Solution(std::istream& input = std::cin);
void RunTests();

int GCD(int lhs, int rhs);
int GCD(const std::array<int, kMaxSize>& data, size_t size);

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
  std::array<int, kMaxSize> data;
  size_t idx = 0;
  while (n--) {
    input >> data[idx++];
  }
  size_t size = idx;

  auto lcm = [](int lhs, int rhs) { return lhs / GCD(lhs, rhs) * rhs; };
  std::array<int, kMaxSize> curr_data;

  int result = lcm(data[0], data[1]);
  for (size_t i = 0; i < size; ++i) {
    size_t curr_idx = 0;
    for (size_t j = i + 1; j < size; ++j) {
      curr_data[curr_idx++] = data[j] / GCD(data[i], data[j]);
    }
    result = GCD(result, data[i] * GCD(curr_data, curr_idx));
  }
  std::cout << result << '\n';
}

int GCD(const std::array<int, kMaxSize>& data, size_t size) {
  int result = data[0];
  for (size_t i = 1; i < size; ++i) {
    result = GCD(result, data[i]);
  }
  return result;
}

int GCD(int lhs, int rhs) {
  while (lhs && rhs) {
    if (lhs > rhs) {
      lhs %= rhs;
    } else {
      rhs %= lhs;
    }
  }
  return std::max(lhs, rhs);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
1 1
)";
    Solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
10 24 40 80
)";
    Solution(ss);
    std::cout << "expected = 40\n";
  }
  {
    std::stringstream ss;
    ss << R"(10
540 648 810 648 720 540 594 864 972 648
)";
    Solution(ss);
    std::cout << "expected = 54\n";
  }
}
