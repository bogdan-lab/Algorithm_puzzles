#include <algorithm>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

struct Ratio {
  uint64_t num;
  uint64_t den;
};

struct S {
  Ratio r;
  int num;
};

enum class CompareResult { kLeftBigger, kLeftSmaller, kEqual };

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

uint64_t GCD(uint64_t l, uint64_t r) {
  if (l > r) std::swap(l, r);
  while (l) {
    r %= l;
    std::swap(l, r);
  }
  return r;
}

uint64_t LCM(uint64_t a, uint64_t b) { return (a * b) / GCD(a, b); }

CompareResult CompareRatiosGreater(const Ratio& l, const Ratio& r) {
  uint64_t lcm = LCM(l.den, r.den);
  uint64_t l_norm = (lcm / l.den) * l.num;
  uint64_t r_norm = (lcm / r.den) * r.num;
  if (l_norm == r_norm) {
    return CompareResult::kEqual;
  } else if (l_norm > r_norm) {
    return CompareResult::kLeftBigger;
  } else {
    return CompareResult::kLeftSmaller;
  }
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<S> data(n);
  int i = 1;
  for (auto& el : data) {
    uint64_t a, b;
    input >> a >> b;
    el.r = Ratio{a, a + b};
    el.num = i++;
  }

  std::sort(data.begin(), data.end(), [](const S& l, const S& r) {
    auto comp_res = CompareRatiosGreater(l.r, r.r);
    switch (comp_res) {
      case CompareResult::kEqual:
        return l.num < r.num;
      case CompareResult::kLeftBigger:
        return true;
      case CompareResult::kLeftSmaller:
        return false;
    }
    return false;
  });

  for (const auto& el : data) {
    std::cout << el.num << ' ';
  }
  std::cout << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
