#include <iostream>
#include <sstream>

int64_t calc_traces(int n, int k, int d) {
  if (n == d || n == 0) return 1;
  if (n < d) return 0;
  int64_t res = 0;
  for (int i = 1; i < d; i++) {
    res += calc_traces(n - i, k, d);
  }
  for (int i = d; i <= k; ++i) {
    res += calc_traces(n - i, k, 1);
  }
  return res;
}

int64_t solution(std::istream& input = std::cin) {
  int n, k, d;
  input >> n >> k >> d;
  return calc_traces(n, k, d);
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(3 3 2)";
    int64_t res = solution(ss);
    std::cout << res << '\n';
  }
  {
    std::stringstream ss;
    ss << R"(3 3 3)";
    int64_t res = solution(ss);
    std::cout << res << '\n';
  }
  {
    std::stringstream ss;
    ss << R"(4 3 2)";
    int64_t res = solution(ss);
    std::cout << res << '\n';
  }
  {
    std::stringstream ss;
    ss << R"(4 5 2)";
    int64_t res = solution(ss);
    std::cout << res << '\n';
  }
  {
    std::stringstream ss;
    ss << R"(6 3 2)";
    int64_t res = solution(ss);
    std::cout << res << '\n';
    std::cout << "expect 18 ???\n";
  }
}

int main() {
  //run_tests();
  std::cout << solution(std::cin) % 1000'000'007 << '\n';
  return 0;
}
