#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

uint64_t CalcOneRealization(const std::vector<int>& stable,
                            const std::vector<int>& rev, uint64_t stable_result,
                            int left, int right);

uint64_t CalcStableResult(const std::vector<int>& lhs,
                          const std::vector<int>& rhs);

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

  uint64_t stable_result = CalcStableResult(stable, rev);
  uint64_t ans = stable_result;
  for (int i = 1; i < stable.size(); ++i) {
    ans =
        std::max({ans, CalcOneRealization(stable, rev, stable_result, i - 1, i),
                  CalcOneRealization(stable, rev, stable_result, i, i)});
  }
  std::cout << ans << '\n';
}

uint64_t CalcOneRealization(const std::vector<int>& stable,
                            const std::vector<int>& rev, uint64_t stable_result,
                            int left, int right) {
  uint64_t ans = stable_result;
  uint64_t prev_value = stable_result;
  while (left > 0 && right < rev.size()) {
    prev_value -= stable[left] * rev[left] + stable[right] * rev[right];
    prev_value += stable[left] * rev[right] + stable[right] * rev[left];
    ans = std::max(ans, prev_value);
    --left;
    ++right;
  }
  return ans;
}

uint64_t CalcStableResult(const std::vector<int>& lhs,
                          const std::vector<int>& rhs) {
  uint64_t result = 0;
  for (size_t i = 0; i < lhs.size(); ++i) {
    result += lhs[i] * rhs[i];
  }
  return result;
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
