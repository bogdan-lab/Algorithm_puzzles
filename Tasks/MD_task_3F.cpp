#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

constexpr double EPSILON = 1e-5;

void solution(std::istream& input = std::cin);
void run_tests();
double travel_time(int v_p, int v_f, double a, double x_cross);
double calc_cross_point(int v_p, int v_f, double a);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int v_p;
  int v_f;
  double a;
  input >> v_p >> v_f >> a;
  std::cout << std::setprecision(5) << std::fixed
            << calc_cross_point(v_p, v_f, a) << '\n';
}

double travel_time(int v_p, int v_f, double a, double x_cross) {
  return v_p * std::sqrt(a * a + (x_cross - 1) * (x_cross - 1)) +
         v_f * std::sqrt((a - 1) * (a - 1) + x_cross * x_cross);
}

double calc_cross_point(int v_p, int v_f, double a) {
  double x_left = 0;
  double x_right = 1;
  size_t iter_num = std::log2(x_right / EPSILON) / std::log2(1.5);
  while (iter_num--) {
    double step = (x_right - x_left) / 3;
    double lhs_mid = x_left + step;
    double rhs_mid = lhs_mid + step;
    if (travel_time(v_p, v_f, a, lhs_mid) >=
        travel_time(v_p, v_f, a, rhs_mid)) {
      x_left = lhs_mid;
    } else {
      x_right = rhs_mid;
    }
  }
  return (x_left + x_right) / 2;
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(5 3
0.4
)";
    solution(ss);
    std::cout << "expected = 0.783310604\n";
  }
}
