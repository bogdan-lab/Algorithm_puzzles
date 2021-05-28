#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

constexpr int64_t mod = 1'000'000'000 + 7;

int64_t dynamic_calc(int n, int k, int d) {
  std::vector<int64_t> bad;
  std::vector<int64_t> good;
  bad.push_back(1);
  good.push_back(0);
  for (int i = 1; i <= n; ++i) {
    int64_t next_good = 0;
    int64_t next_bad = 0;
    // Calculate bad
    for (int j = 1; j <= std::min(d - 1, i); ++j) {
      next_bad += bad[i - j];
    }
    // Calculate good
    for (int j = 1; j <= std::min(d - 1, i); ++j) {
      next_good += good[i - j];
    }
    for (int j = d; j <= std::min(i, k); ++j) {
      next_good += bad[i - j] + good[i - j];
    }
    // Save results
    while (next_bad > mod) next_bad -= mod;
    while (next_good > mod) next_good -= mod;
    bad.push_back(next_bad);
    good.push_back(next_good);
  }
  return good.back();
}

int64_t recursive_calc(int n, int k, int d) {
  if (n == d || n == 0) return 1;
  if (n < d) return 0;
  int64_t res = 0;
  for (int i = 1; i < d; i++) {
    res += recursive_calc(n - i, k, d);
  }
  for (int i = d; i <= k; ++i) {
    res += recursive_calc(n - i, k, 1);
  }
  return res;
}

int64_t solution(std::istream& input = std::cin) {
  int n, k, d;
  input >> n >> k >> d;
  // return recursive_calc(n, k, d);
  return dynamic_calc(n, k, d);
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(3 3 2)";
    int64_t res = solution(ss);
    std::cout << res << " == 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 3 3)";
    int64_t res = solution(ss);
    std::cout << res << " == 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 3 2)";
    int64_t res = solution(ss);
    std::cout << res << " == 6\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 5 2)";
    int64_t res = solution(ss);
    std::cout << res << " == 7\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 100 1)";
    int64_t res = solution(ss);
    std::cout << res << " == 16\n";
  }
}

int main() {
  // run_tests();
  std::cout << solution(std::cin) % mod << '\n';
  return 0;
}
