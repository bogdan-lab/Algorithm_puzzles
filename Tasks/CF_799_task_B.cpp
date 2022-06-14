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
  while (t--) {
    size_t n;
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::sort(data.begin(), data.end());
    auto last = std::unique(data.begin(), data.end());
    size_t unique_count = last - data.begin();
    if ((n - unique_count) % 2) {
      std::cout << unique_count - 1 << '\n';
    } else {
      std::cout << unique_count << '\n';
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
6
2 2 2 3 3 3
5
9 1 9 9 1
4
15 16 16 15
4
10 100 1000 10000
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
