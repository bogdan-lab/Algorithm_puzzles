#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct DayPill {
  int days;
  int64_t pills;
};

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int64_t GetPillsNum(int day_index, const std::vector<DayPill>& data) {
  int64_t res = 0;
  for (const auto& el : data) {
    if (el.days > day_index) {
      res += el.pills;
    }
  }
  return res;
}

void Solution(std::istream& input) {
  int n;
  int64_t k;
  input >> n >> k;
  std::vector<DayPill> data(n);
  int max_days = 0;
  for (auto& el : data) {
    input >> el.days >> el.pills;
    max_days = std::max(max_days, el.days);
  }

  int64_t left = -1;
  int64_t right = max_days + 1;
  while (right - left > 1) {
    int64_t mid = (left + right) / 2;
    if (GetPillsNum(mid, data) <= k) {
      right = mid;
    } else {
      left = mid;
    }
  }
  std::cout << right + 1 << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
