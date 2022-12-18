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

int CalcMinOperations(std::vector<int>& data, int x) {
  int count = 0;
  for (int i = 1; i < data.size(); ++i) {
    if (data[i] < data[i - 1]) {
      // need to move down point in d[i-1]
      int index =
          std::upper_bound(data.begin(), data.begin() + i, x) - data.begin();
      if (index == i) return -1;
      while (index < i) {
        if (data[index] > x) {
          std::swap(data[index], x);
          ++count;
        }
        ++index;
      }
      // check that state has changed
      if (data[i] < data[i - 1]) {
        return -1;
      }
    }
  }
  return count;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n, x;
    input >> n >> x;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }

    std::cout << CalcMinOperations(data, x) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
4 1
2 3 5 4
5 6
1 1 3 4 4
1 10
2
2 10
11 9
2 10
12 11
5 18
81 324 218 413 324
)";
    Solution(ss);
    std::cout << "expected = 3; 0; 0; -1; 1; 3\n";
  }
}
