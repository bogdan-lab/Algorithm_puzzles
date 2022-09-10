#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

uint64_t GCD(uint64_t l, uint64_t r);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  int n;
  while (t--) {
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::sort(data.begin(), data.end());
    uint64_t lcm = data.front();
    for (int i = 1; i < data.size(); ++i) {
      lcm = (lcm * data[i]) / GCD(lcm, data[i]);
    }

    if (lcm == data.back()) {
      lcm *= 2;
    }

    int idx = 0;
    for (uint64_t i = 2; i < lcm; ++i) {
      if (lcm % i) continue;
      if (idx < data.size() && i == data[idx]) {
        ++idx;
      } else {
        std::cout << "-1\n";
        return;
      }
    }

    std::cout << lcm << '\n';
  }
}

uint64_t GCD(uint64_t l, uint64_t r) {
  while (l && r) {
    if (l > r) {
      l %= r;
    } else {
      r %= l;
    }
  }
  return l ? l : r;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
8
8 2 12 6 4 24 16 3
1
2
2
3 4
)";
    Solution(ss);
    std::cout << "expected = 48; 4; -1\n";
  }
}
