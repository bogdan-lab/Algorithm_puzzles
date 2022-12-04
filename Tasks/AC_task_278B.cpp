#include <iostream>
#include <sstream>
#include <utility>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

bool IsValid(std::pair<int, int> t) { return t.first <= 23 && t.second <= 59; }

std::pair<int, int> NextTime(int h, int m) {
  ++m;
  if (m == 60) {
    m = 0;
    h = (h + 1) % 24;
  }
  return {h, m};
}

std::pair<int, int> Switch(std::pair<int, int> t) {
  int a = t.first / 10;
  int b = t.first - a * 10;
  int c = t.second / 10;
  int d = t.second - c * 10;
  return {a * 10 + c, b * 10 + d};
}

void Solution(std::istream& input) {
  std::pair<int, int> t;
  input >> t.first >> t.second;

  while (true) {
    if (IsValid(Switch(t))) break;
    t = NextTime(t.first, t.second);
  }

  std::cout << t.first << ' ' << t.second << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(1 23
)";
    Solution(ss);
    std::cout << "expected = 1 23\n";
  }
  {
    std::stringstream ss;
    ss << R"(19 57
)";
    Solution(ss);
    std::cout << "expected = 20 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(20 40
)";
    Solution(ss);
    std::cout << "expected = 21 0\n";
  }
}
