#include <iostream>
#include <sstream>

constexpr uint64_t kMaxValue = 3ULL * 1'000'000'000ULL;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

uint64_t SQRT(uint64_t n) {
  uint64_t r = kMaxValue;
  uint64_t l = 0;
  while (r - l > 1) {
    uint64_t m = (l + r) / 2;
    if (m * m < n) {
      l = m;
    } else {
      r = m;
    }
  }
  return r;
}

void SolveOne(std::istream& input) {
  uint64_t n;
  input >> n;

  for (uint64_t i = 2; i < n; ++i) {
    if (!(n % i)) {
      n /= i;
      if (!(n % i)) {
        // i - p
        n /= i;
        std::cout << i << ' ' << n << '\n';
      } else {
        // i - q
        std::cout << SQRT(n) << ' ' << i << '\n';
      }
      return;
    }
  }
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
