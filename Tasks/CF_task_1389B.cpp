#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
int CalcMaxScore(const std::vector<int>& vec, int max_steps, int max_left);

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
    int n;
    int max_steps;
    int max_left;
    input >> n >> max_steps >> max_left;
    std::vector<int> array(n);
    for (auto& el : array) {
      input >> el;
    }
    std::cout << CalcMaxScore(array, max_steps, max_left) << '\n';
  }
}

int CalcMaxScore(const std::vector<int>& data, int max_steps, int max_left) {
  int res = std::accumulate(data.begin(), data.begin() + max_steps + 1, 0);
  for (int left = 1; left < max_left + 1; ++left) {
    int tmp = 0;
    int max_val = 0;
    int guaranteed_steps = max_steps - 2 * left;
    if (guaranteed_steps < 0) continue;
    for (int i = 0; i < guaranteed_steps + 1; ++i) {
      max_val = std::max(max_val, data[i] + data[i + 1]);
      tmp += data[i];
    }
    res = std::max(res, tmp + left * max_val);
  }
  return res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
5 4 0
1 5 4 3 2
5 4 1
1 5 4 3 2
5 4 4
10 20 30 40 50
10 7 3
4 6 8 2 9 9 7 4 10 9
)";
    Solution(ss);
    std::cout << "expected = 15; 19; 150; 56\n";
  }
}
