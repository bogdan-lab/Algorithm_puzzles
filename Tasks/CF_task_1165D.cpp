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

void Solution(std::istream& input) {
  int t;
  input >> t;

  int n;
  while (t--) {
    input >> n;
    std::vector<uint64_t> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::sort(data.begin(), data.end());

    uint64_t lcm = data.front() * data.back();

    std::vector<uint64_t> div;
    for (uint64_t i = 2; i * i <= lcm; ++i) {
      if (lcm % i) continue;
      div.push_back(i);
      if (i != lcm / i) {
        div.push_back(lcm / i);
      }
    }

    std::sort(div.begin(), div.end());

    if (div == data) {
      std::cout << lcm << '\n';
    } else {
      std::cout << "-1\n";
    }
  }
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
