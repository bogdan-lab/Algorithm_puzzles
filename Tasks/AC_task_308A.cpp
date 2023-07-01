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
  int n = 8;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  if (!std::is_sorted(data.begin(), data.end())) {
    std::cout << "No\n";
    return;
  }

  if (data.front() < 100 || data.back() > 675) {
    std::cout << "No\n";
    return;
  }

  if (!std::all_of(data.begin(), data.end(),
                   [](int val) { return (val % 25) == 0; })) {
    std::cout << "No\n";
    return;
  }

  std::cout << "Yes\n";
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
