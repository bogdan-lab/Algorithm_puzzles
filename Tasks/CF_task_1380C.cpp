#include <algorithm>
#include <functional>
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

void SolveOne(std::istream& input) {
  int n, x;
  input >> n >> x;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }
  std::sort(data.begin(), data.end(), std::greater<int>());

  int count = 0;

  int prev_index = -1;
  for (int i = 0; i < data.size(); ++i) {
    if (data[i] * (i - prev_index) >= x) {
      ++count;
      prev_index = i;
    }
  }
  std::cout << count << '\n';
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
