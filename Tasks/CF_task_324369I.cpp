#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct Value {
  uint64_t v = 0;
  bool is_pos = true;
};

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
  return (cur >> 8);
}

void Solution(std::istream& input) {
  int m, q;
  input >> m >> q;
  uint32_t a, b;
  input >> a >> b;

  std::vector<Value> data((1UL << 24));
  while (m--) {
    uint32_t adding = nextRand(a, b);
    uint32_t l = nextRand(a, b);
    uint32_t r = nextRand(a, b);
    if (l > r) std::swap(l, r);
    ++r;

    if (data[l].is_pos) {
      data[l].v += adding;
    } else {
      if (data[l].v > adding) {
        data[l].v -= adding;
      } else {
        data[l].v = adding - data[l].v;
        data[l].is_pos = true;
      }
    }
    if (r < data.size()) {
      if (!data[r].is_pos) {
        data[r].v += adding;
      } else {
        if (data[r].v >= adding) {
          data[r].v -= adding;
        } else {
          data[r].v = adding - data[r].v;
          data[r].is_pos = false;
        }
      }
    }
  }

  for (int j = 0; j < 2; ++j) {
    for (int i = 1; i < data.size(); ++i) {
      if (data[i].is_pos) {
        data[i].v += data[i - 1].v;
      } else {
        data[i].v = data[i - 1].v - data[i].v;
      }
      data[i].is_pos = true;
    }
  }

  uint32_t res = 0;
  while (q--) {
    uint32_t l = nextRand(a, b);
    uint32_t r = nextRand(a, b);
    if (l > r) std::swap(l, r);
    if (l > 0) {
      res += data[r].v - data[l - 1].v;
    } else {
      res += data[r].v;
    }
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
