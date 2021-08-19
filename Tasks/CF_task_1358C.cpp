#include <iostream>
#include <sstream>

void solution(std::istream& input = std::cin);
void run_tests();
uint64_t solve_one_case(int x1, int y1, int x2, int y2) {
  uint64_t x_len = x2 - x1;
  uint64_t y_len = y2 - y1;
  return 1 + x_len * y_len;
}

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) {
    int x1, y1, x2, y2;
    input >> x1 >> y1 >> x2 >> y2;
    std::cout << solve_one_case(x1, y1, x2, y2) << '\n';
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(4
1 1 2 2
1 2 2 4
179 1 179 100000
5 7 5 7
)";
    solution(ss);
    std::cout << "expected = 2 3 1 1\n";
  }
}
