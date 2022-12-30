#include <iostream>
#include <sstream>
#include <vector>

constexpr uint64_t kMaxVal = 1'000'000'000;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

uint64_t GetPower(uint64_t val) {
  uint64_t res = 1;
  while (10 * res <= val) {
    res *= 10;
  }
  return res;
}

void SolveOne(std::istream& input) {
  uint64_t val = 0;
  input >> val;
  uint64_t div = GetPower(val);
  std::vector<int> data;
  while (div) {
    data.push_back(val / div);
    val %= div;
    div /= 10;
  }

  uint64_t l = 0;
  uint64_t r = 0;
  for (int i = 0; i < data.size(); ++i) {
    if (i & 1) {
      r = 10 * r + data[i];
    } else {
      l = 10 * l + data[i];
    }
  }

  std::cout << (l + 1) * (r + 1) - 2 << '\n';
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) {
    SolveOne(input);
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
100
12
8
2021
10000
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
