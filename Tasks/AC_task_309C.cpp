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

void Add(std::vector<int64_t>& data, const DayPill& dp) {
  data[0] += dp.pills;
  if (dp.days < data.size()) {
    data[dp.days] -= dp.pills;
  }
}

void BuildPrefix(std::vector<int64_t>& data) {
  for (int i = 1; i < data.size(); ++i) {
    data[i] += data[i - 1];
  }
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

  std::vector<int64_t> total(max_days + 1);
  for (const auto& el : data) {
    Add(total, el);
  }

  BuildPrefix(total);

  auto it = std::find_if(total.begin(), total.end(),
                         [&](int64_t val) { return val <= k; });

  std::cout << (it - total.begin()) + 1 << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
