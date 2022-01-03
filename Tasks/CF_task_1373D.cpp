#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
uint64_t CalcEvenSum(const std::vector<int>& vec);
uint64_t CalcBestEvenSum(const std::vector<int>& vec);
bool IsEven(int val);
uint64_t CalcBestEvenSum2(const std::vector<int>& vec);

uint64_t AccumulatePositiveChanges(const std::vector<int>& vec);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t = 0;
  input >> t;
  while (t--) {
    int n = 0;
    input >> n;
    std::vector<int> vec(n);
    for (auto& el : vec) {
      input >> el;
    }
    std::cout << CalcBestEvenSum2(vec) << '\n';
  }
}

uint64_t CalcEvenSum(const std::vector<int>& vec) {
  uint64_t res = 0;
  for (size_t i = 0; i < vec.size(); i += 2) {
    res += vec[i];
  }
  return res;
}

uint64_t CalcBestEvenSum(const std::vector<int>& vec) {
  std::vector<std::vector<uint64_t>> data(vec.size());
  for (auto& el : data) {
    el.resize(vec.size());
  }
  uint64_t init_sum = CalcEvenSum(vec);
  for (int i = 0; i < data.size(); ++i) {
    data[i][i] = init_sum;
  }
  uint64_t res = init_sum;
  for (int l = 0; l < vec.size(); ++l) {
    for (int r = l + 1; r < vec.size(); r += 2) {
      uint64_t base = r - l > 1 ? data[l][r - 2] : init_sum;
      int change = IsEven(r) ? vec[r - 1] - vec[r] : vec[r] - vec[r - 1];
      data[l][r] = base + change;
      res = std::max(res, data[l][r]);
    }
  }
  return res;
}

uint64_t AccumulatePositiveChanges(const std::vector<int>& vec) {
  uint64_t from_start = 0;
  uint64_t sum = 0;
  for (int i = 1; i < vec.size(); i += 2) {
    int change = vec[i] - vec[i - 1];
    sum = (change < 0 && sum < -change) ? 0 : sum + change;
    from_start = std::max(sum, from_start);
  }
  uint64_t from_first = 0;
  sum = 0;
  for (int i = 2; i < vec.size(); i += 2) {
    int change = vec[i - 1] - vec[i];
    sum = (change < 0 && sum < -change) ? 0 : sum + change;
    from_first = std::max(from_first, sum);
  }
  return std::max(from_first, from_start);
}

uint64_t CalcBestEvenSum2(const std::vector<int>& vec) {
  uint64_t init_sum = CalcEvenSum(vec);
  return init_sum + AccumulatePositiveChanges(vec);
}

bool IsEven(int val) { return !(val % 2); }

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
8
1 7 3 4 7 6 2 9
5
1 2 1 2 1
10
7 8 4 5 7 6 8 9 7 3
4
3 1 2 1
)";
    Solution(ss);
    std::cout << "expected = 26; 5; 37; 5\n";
  }
}
