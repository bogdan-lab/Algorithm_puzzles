#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

constexpr double EPSILON = 1e-7;

void solution(std::istream& input = std::cin);
void run_tests();
double solve_for(double c);
double func(double x);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  double c;
  input >> c;
  std::cout << std::setprecision(7) << std::fixed << solve_for(c) << '\n';
}

double solve_for(double c) {
  double x_left = 0;
  double x_right = c;
  size_t iter_num = std::log2(x_right / EPSILON);
  while (iter_num--) {
    double mid = (x_left + x_right) / 2;
    if (func(mid) > c) {
      x_right = mid;
    } else {
      x_left = mid;
    }
  }
  return (x_left + x_right) / 2;
}

double func(double x) { return x * x + std::sqrt(x); }

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(2.0000000000
)";
    solution(ss);
    std::cout << "expected = 1.0\n";
  }
  {
    std::stringstream ss;
    ss << R"(18.0000000000
)";
    solution(ss);
    std::cout << "expected = 4.0\n";
  }
}
