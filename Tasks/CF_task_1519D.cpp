#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<uint64_t> GetIntegral(const std::vector<int>& lhs,
                                  const std::vector<int>& rhs);
uint64_t CalcRealization(const std::vector<int>& stable,
                         const std::vector<int>& rev,
                         const std::vector<uint64_t>& integral, int start_rev,
                         int end_rev);
uint64_t CalcOutSum(const std::vector<uint64_t>& integral, int start_gap,
                    int end_gap);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> rev(n);
  for (auto& el : rev) {
    input >> el;
  }
  std::vector<int> stable(n);
  for (auto& el : stable) {
    input >> el;
  }
  std::vector<uint64_t> integral = GetIntegral(rev, stable);
  uint64_t ans = integral.back();
  int window_width = 1;
  while (window_width < stable.size()) {
    for (int i = 0; i < stable.size() - window_width; ++i) {
      ans = std::max(
          ans, CalcRealization(stable, rev, integral, i, i + window_width));
    }
    ++window_width;
  }
  std::cout << ans << '\n';
}

std::vector<uint64_t> GetIntegral(const std::vector<int>& lhs,
                                  const std::vector<int>& rhs) {
  std::vector<uint64_t> result(lhs.size());
  result.front() = lhs.front() * rhs.front();
  for (size_t i = 1; i < lhs.size(); ++i) {
    result[i] = result[i - 1] + lhs[i] * rhs[i];
  }
  return result;
}

uint64_t CalcRealization(const std::vector<int>& stable,
                         const std::vector<int>& rev,
                         const std::vector<uint64_t>& integral, int start_rev,
                         int end_rev) {
  uint64_t result = CalcOutSum(integral, start_rev, end_rev);
  for (int i = start_rev, j = end_rev; i <= end_rev; ++i, --j) {
    result += stable[i] * rev[j];
  }
  return result;
}

uint64_t CalcOutSum(const std::vector<uint64_t>& integral, int start_gap,
                    int end_gap) {
  return integral.back() - integral[end_gap] +
         (start_gap > 0 ? integral[start_gap - 1] : 0ULL);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
2 3 2 1 3
1 3 2 4 2
)";
    Solution(ss);
    std::cout << "expected = 29\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
13 37
2 4
)";
    Solution(ss);
    std::cout << "expected = 174\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
1 8 7 6 3 6
5 9 6 8 8 6
)";
    Solution(ss);
    std::cout << "expected = 235\n";
  }
}
