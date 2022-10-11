#include <algorithm>
#include <iostream>
#include <limits>
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

int GetThickness(const std::vector<int>& prefix, int sum_val) {
  int res = 0;
  int curr_val = sum_val;
  auto prev = prefix.begin();
  while (true) {
    auto next = find(prev + 1, prefix.end(), curr_val);
    if (next == prefix.end()) return std::numeric_limits<int>::max();
    res = std::max<int>(res, next - prev);
    if (next == --prefix.end()) break;
    prev = next;
    curr_val += sum_val;
  }
  return res;
}

int GetAnswer(const std::vector<int>& data) {
  std::vector<int> prefix(data.size() + 1);
  for (size_t i = 1; i < prefix.size(); ++i) {
    prefix[i] = prefix[i - 1] + data[i - 1];
  }

  int res = std::numeric_limits<int>::max();
  for (int i = 1; i < prefix.size(); ++i) {
    res = std::min(res, GetThickness(prefix, prefix[i]));
  }

  return res;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }

    std::cout << GetAnswer(data) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
6
55 45 30 30 40 100
4
10 23 7 13
5
10 55 35 30 65
6
4 1 1 1 1 4
2
1 2
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
