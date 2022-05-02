#include <iostream>
#include <sstream>

struct Res {
  int a = 0;
  int b = 0;
};

Res GetNumbers(int x, int y);

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
    int x, y;
    input >> x >> y;
    Res res = GetNumbers(x, y);
    std::cout << res.a << ' ' << res.b << '\n';
  }
}

Res GetNumbers(int x, int y) {
  Res res;
  if (y < x || (y % x)) return res;
  if (y == x) {
    res.a = 1;
    res.b = 1;
    return res;
  }
  res.a = 1;
  res.b = y / x;
  return res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
3 75
100 100
42 13
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
