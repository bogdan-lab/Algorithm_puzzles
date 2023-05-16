#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
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

bool Check(const std::vector<int>& data, const std::vector<int>& arr,
           uint64_t sum) {
  uint64_t res = 0;
  for (size_t i = 0; i < data.size(); ++i) {
    res += data[i] > arr[i] ? data[i] - arr[i] : arr[i] - data[i];
  }
  return 2 * res <= sum;
}

std::vector<int> Build(std::vector<int> data, const std::vector<int>& arr,
                       size_t start) {
  for (size_t i = start; i < data.size(); i += 2) {
    data[i] = arr[i];
  }
  return data;
}

void PrintRes(const std::vector<int>& res) {
  for (const auto& el : res) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void SolveOne(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }
  uint64_t sum = std::accumulate(data.begin(), data.end(), 0ULL);

  auto res = Build(std::vector<int>(n, 1), data, 0);
  if (Check(res, data, sum)) {
    PrintRes(res);
    return;
  }
  PrintRes(Build(std::vector<int>(n, 1), data, 1));
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
5
1 2 3 4 5
2
4 6
2
1 1000000000
6
3 4 8 1 2 3
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
