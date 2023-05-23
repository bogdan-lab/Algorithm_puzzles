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

std::vector<int> BuildArray(int n, int s) {
  int level = s / n;
  std::vector<int> data(n, level);
  data[0] += s - n * level;
  return data;
}

void PrintArray(const std::vector<int>& data) {
  for (const auto& el : data) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void Solution(std::istream& input) {
  int n, s;
  input >> n >> s;

  if (s / n >= 2) {
    std::cout << "YES\n";
    PrintArray(BuildArray(n, s));
    std::cout << 1 << '\n';
  } else {
    std::cout << "NO\n";
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
