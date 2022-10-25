#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

uint32_t cur = 0;
uint32_t nextRand(uint32_t a, uint32_t b) {
  cur = cur * a + b;
  return cur >> 8;
}

void Solution(std::istream& input) {
  int m, q;
  input >> m >> q;
  uint32_t a, b;
  input >> a >> b;

  std::vector<int64_t> data((1UL << 24));
  while (m--) {
    int64_t adding = nextRand(a, b);
    uint32_t l = nextRand(a, b);
    uint32_t r = nextRand(a, b);
    if (l > r) std::swap(l, r);
    ++r;

    data[l] += adding;
    data[r] -= adding;
  }

  for (int i = 1; i < data.size(); ++i) {
    data[i] += data[i - 1];
  }

  data.insert(data.begin(), 0);

  for (int i = 1; i < data.size(); ++i) {
    data[i] += data[i - 1];
  }

  uint32_t res = 0;
  while (q--) {
    uint32_t l = nextRand(a, b);
    uint32_t r = nextRand(a, b);
    if (l > r) std::swap(l, r);
    ++r;
    res += data[r] - data[l];
  }
  std::cout << res << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5 5
0 257
)";
    Solution(ss);
    std::cout << "expected = 25\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 5
13 239
)";
    Solution(ss);
    std::cout << "expected = 811747796\n";
  }
  {
    std::stringstream ss;
    ss << R"(10 10
239017 170239
)";
    Solution(ss);
    std::cout << "expected = 3460675938\n";
  }
}
