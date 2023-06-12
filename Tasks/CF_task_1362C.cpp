#include <iostream>
#include <sstream>
#include <vector>

constexpr int kMaxPower = 64;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::vector<uint64_t> BuildTable(int power) {
  std::vector<uint64_t> res(power + 1);
  res[0] = 1;
  for (size_t i = 1; i < res.size(); ++i) {
    res[i] = 2 * res[i - 1] + 1;
  }
  return res;
}

int GetPower(uint64_t val) {
  int p = 0;
  while (val / 2 > 0) {
    val /= 2;
    ++p;
  }
  return p;
}

std::vector<uint64_t> BuildPowers(int p) {
  std::vector<uint64_t> res;
  res.reserve(p + 1);
  uint64_t curr = 1;
  for (int i = 0; i <= p; ++i) {
    res.push_back(curr);
    curr *= 2;
  }
  return res;
}

uint64_t CalcDifference(uint64_t n, const std::vector<uint64_t>& dp,
                        const std::vector<uint64_t>& powers) {
  if (n == 0) return 0;
  int pow = GetPower(n);
  uint64_t res = n - powers[pow];
  return dp[pow] + CalcDifference(res, dp, powers);
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  std::vector<uint64_t> dp = BuildTable(kMaxPower);
  std::vector<uint64_t> powers = BuildPowers(kMaxPower);
  while (t--) {
    uint64_t n;
    input >> n;
    std::cout << CalcDifference(n, dp, powers) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
