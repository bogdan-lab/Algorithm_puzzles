#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
uint64_t CalcMinimumScore(int k, const std::vector<uint64_t>& data);
uint64_t CalcFromBack(std::vector<uint64_t>& data);

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
    int k = 0;
    input >> n >> k;
    std::vector<uint64_t> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::sort(data.begin(), data.end());
    std::cout << CalcMinimumScore(k, data) << '\n';
  }
}

uint64_t CalcMinimumScore(int k, const std::vector<uint64_t>& data) {
  std::vector<uint64_t> red(data.end() - 2 * k, data.end());
  uint64_t count = CalcFromBack(red);
  return std::accumulate(data.begin(), data.end() - 2 * k, count);
}

uint64_t CalcFromBack(std::vector<uint64_t>& data) {
  if (data.empty()) return 0ull;
  size_t k = data.size() / 2;
  uint64_t count = 0;
  for (size_t i = 0; i < k; ++i) {
    count += data[i] / data[i + k];
  }
  return count;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(7
7 3
1 1 1 2 1 3 1
5 1
5 5 5 5 5
4 2
1 3 3 7
2 0
4 2
9 2
1 10 10 1 10 2 7 10 3
7 3
1 2 3 5 5 7 8
13 6
1 2 2 2 2 5 6 7 7 9 9 10 11
)";
    Solution(ss);
    std::cout << "expected = 2 16 0 6 16 1 1\n";
  }
}
