#include <array>
#include <iostream>
#include <sstream>
#include <vector>

constexpr size_t kMaxSize = 100'000;

void Solution(std::istream& input = std::cin);
void RunTests();

uint64_t GCD(uint64_t lhs, uint64_t rhs);
uint64_t GCD(const std::array<uint64_t, kMaxSize>& data, size_t size);

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
  std::array<uint64_t, kMaxSize> data;
  size_t idx = 0;
  while (n--) {
    input >> data[idx++];
  }
  size_t size = idx;

  uint64_t shift = GCD(data, size);
  for (size_t i = 0; i < size; ++i) {
    data[i] /= shift;
  }

  std::array<uint64_t, kMaxSize> prefix = data;
  std::array<uint64_t, kMaxSize> sufix = data;

  for (size_t i = 1; i < size; ++i) {
    prefix[i] = GCD(prefix[i - 1], prefix[i]);
  }

  for (size_t i = size - 1; i > 0; --i) {
    sufix[i - 1] = GCD(sufix[i - 1], sufix[i]);
  }

  std::array<uint64_t, kMaxSize> darray;
  for (size_t i = 0; i < size; ++i) {
    if (i == 0) {
      darray[i] = sufix[i + 1];
    } else if (i == size - 1) {
      darray[i] = prefix[i - 1];
    } else {
      darray[i] = GCD(prefix[i - 1], sufix[i + 1]);
    }
  }

  auto lcm = [](uint64_t lhs, uint64_t rhs) {
    return lhs / GCD(lhs, rhs) * rhs;
  };
  uint64_t result = darray[0];
  for (size_t i = 1; i < size; ++i) {
    result = lcm(result, darray[i]);
  }
  std::cout << result * shift << '\n';
}

uint64_t GCD(const std::array<uint64_t, kMaxSize>& data, size_t size) {
  int result = data[0];
  for (size_t i = 1; i < size; ++i) {
    result = GCD(result, data[i]);
  }
  return result;
}

uint64_t GCD(uint64_t lhs, uint64_t rhs) {
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
