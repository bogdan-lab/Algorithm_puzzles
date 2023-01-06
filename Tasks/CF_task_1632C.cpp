#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

uint32_t GetBs(uint32_t as, uint32_t b) {
  uint32_t bs = 0;
  for (int i = 31; i >= 0; --i) {
    uint32_t test = 1U << static_cast<uint32_t>(i);
    if (as & test) {
      bs |= test;
      if (!(b & test)) {
        return bs;
      }
    } else {
      bs |= (b & test);
    }
  }
  return bs;
}

void SolveOne(std::istream& input) {
  uint32_t a, b;
  input >> a >> b;

  uint32_t min_v = std::numeric_limits<uint32_t>::max();
  for (uint32_t as = a; as <= b; ++as) {
    uint32_t bs = GetBs(as, b);
    min_v = std::min(min_v, as + (as | bs) + 1 - a - b);
  }
  std::cout << std::min(min_v, b - a) << '\n';
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
5 8
2 5
3 19
56678 164422
)";
    Solution(ss);
    std::cout << "expected = 1; 3; 2; 1; 23329\n";
  }
}
