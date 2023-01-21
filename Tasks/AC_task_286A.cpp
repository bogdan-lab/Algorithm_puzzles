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
  int n, p, q, r, s;
  input >> n >> p >> q >> r >> s;
  --p;
  --r;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }
  for (int i = r, j = p; i < s; ++i, ++j) {
    std::swap(data[i], data[j]);
  }

  for (const auto& el : data) {
    std::cout << el << ' ';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
