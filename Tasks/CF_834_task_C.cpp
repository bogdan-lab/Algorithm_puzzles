#include <cmath>
#include <iostream>
#include <sstream>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int Count(int64_t l, int64_t r, int64_t x, int64_t a, int64_t b) {
  if (b < l || b > r) return -1;
  if (a == b) return 0;
  if (std::abs(a - b) >= x) return 1;
  if (a + x > r && a - x < l) return -1;
  if (b > a) {
    if (a - x >= l) return 2;
    if (b + x <= r) return 2;
    if (b - x >= l) return 3;
    return -1;
  }
  if (b < a) {
    if (a + x <= r) return 2;
    if (b - x >= l) return 2;
    if (b + x <= r) return 3;
    return -1;
  }
  return -1;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int64_t l, r, x, a, b;
    input >> l >> r >> x >> a >> b;
    std::cout << Count(l, r, x, a, b) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(10
3 5 6
3 3
0 15 5
4 5
0 10 5
3 7
3 5 6
3 4
-10 10 11
-5 6
-3 3 4
1 0
-5 10 8
9 2
1 5 1
2 5
-1 4 3
0 2
-6 3 6
-1 -4
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
