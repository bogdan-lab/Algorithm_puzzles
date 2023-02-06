#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::vector<int> GetNeededToAdd(const std::vector<int>& data, int k) {
  std::vector<int> res;
  res.reserve(data.size());
  for (const auto& el : data) {
    res.push_back(k - (el % k));
  }
  return res;
}

std::vector<int64_t> BuildXDynamic(const std::vector<int>& need_to_add, int k) {
  std::vector<int64_t> res;
  if (need_to_add.front() == k) return res;
  res.reserve(need_to_add.size());
  int64_t cycle_add = 0;
  res.push_back(need_to_add.front());
  for (int i = 1; i < need_to_add.size(); ++i) {
    if (need_to_add[i] == k) break;
    if (need_to_add[i] > need_to_add[i - 1]) {
      cycle_add = 0;
    } else {
      cycle_add += k;
    }
    res.push_back(need_to_add[i] + cycle_add);
  }
  std::sort(res.begin(), res.end());
  return res;
}

int64_t CountSteps(const std::vector<int64_t>& dynamic) {
  int64_t res = 0;
  if (dynamic.empty()) return res;
  res += dynamic.front() + 1;
  for (int i = 1; i < dynamic.size(); ++i) {
    res += dynamic[i] - dynamic[i - 1];
  }
  return res;
}

void SolveOne(std::istream& input) {
  int n, k;
  input >> n >> k;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<int> need_to_add = GetNeededToAdd(data, k);
  std::sort(need_to_add.begin(), need_to_add.end());
  std::vector<int64_t> dynamic = BuildXDynamic(need_to_add, k);

  std::cout << CountSteps(dynamic) << '\n';
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
