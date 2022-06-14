#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int CalcMinOperNumber(const std::vector<int>& data, int sum);
std::vector<int> BuildPrefix(const std::vector<int>& data);

std::vector<int> RemoveCostLeft(const std::vector<int>& data);
std::vector<int> RemoveCostRight(const std::vector<int>& data);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n, s;
    input >> n >> s;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::cout << CalcMinOperNumber(data, s) << '\n';
  }
}

std::vector<int> BuildPrefix(const std::vector<int>& data) {
  std::vector<int> result(data.size());
  result[0] = data[0];
  for (size_t i = 1; i < data.size(); ++i) {
    result[i] = result[i - 1] + data[i];
  }
  return result;
}

std::vector<int> RemoveCostLeft(const std::vector<int>& data) {
  std::vector<int> result;
  result.push_back(0);
  for (int i = 0; i < data.size(); ++i) {
    if (data[i]) {
      result.push_back(i + 1);
    }
  }
  return result;
}

std::vector<int> RemoveCostRight(const std::vector<int>& data) {
  std::vector<int> result;
  result.push_back(0);
  for (int i = data.size() - 1; i >= 0; --i) {
    if (data[i]) {
      result.push_back(data.size() - i);
    }
  }
  return result;
}

int CalcMinOperNumber(const std::vector<int>& data, int sum) {
  int curr_sum = std::accumulate(data.begin(), data.end(), 0);
  if (curr_sum == sum) return 0;
  if (curr_sum < sum) return -1;
  int count_to_delete = curr_sum - sum;
  std::vector<int> L = RemoveCostLeft(data);
  std::vector<int> R = RemoveCostRight(data);
  std::vector<int> possible_costs;
  for (int i = 0; i < count_to_delete + 1; ++i) {
    possible_costs.push_back(L[i] + R[count_to_delete - i]);
  }
  return *std::min_element(possible_costs.begin(), possible_costs.end());
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(7
3 1
1 0 0
3 1
1 1 0
9 3
0 1 0 1 1 1 0 0 1
6 4
1 1 1 1 1 1
5 1
0 0 1 1 0
16 2
1 1 0 0 1 0 0 1 1 0 0 0 0 0 1 1
6 3
1 0 1 0 0 0
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
