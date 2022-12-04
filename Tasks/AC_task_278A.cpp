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
  int n, k;
  input >> n >> k;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  if (k >= n) {
    for (int i = 0; i < n; ++i) {
      std::cout << "0 ";
    }
    std::cout << "\n";
    return;
  }

  for (int i = k; i < n; ++i) {
    std::cout << data[i] << ' ';
  }
  for (int i = 0; i < k; ++i) {
    std::cout << "0 ";
  }
  std::cout << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 2
2 7 8
)";
    Solution(ss);
    std::cout << "expected = 8 0 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 4
9 9 9
)";
    Solution(ss);
    std::cout << "expected = 0 0 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(9 5
1 2 3 4 5 6 7 8 9
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
