#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

bool CheckSum(const std::vector<int>& data);

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
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::cout << (CheckSum(data) ? "YES\n" : "NO\n");
  }
}

bool CheckSum(const std::vector<int>& data) {
  std::vector<int> rem(10);
  for (const auto& el : data) {
    ++rem[el % 10];
  }
  // Check tripples
  for (int i = 0; i < rem.size(); ++i) {
    if (rem[i] >= 3 && ((3 * i) % 10) == 3) {
      return true;
    }
  }
  // Check doubles
  for (int i = 0; i < rem.size(); ++i) {
    for (int j = 0; j < rem.size(); ++j) {
      if (i != j && rem[i] >= 2 && rem[j] >= 1 && ((2 * i + j) % 10) == 3) {
        return true;
      }
    }
  }
  // Check singles
  for (int i = 0; i < rem.size(); ++i) {
    for (int j = 0; j < rem.size(); ++j) {
      for (int k = 0; k < rem.size(); ++k) {
        if (i != j && j != k && i != k && rem[i] && rem[j] && rem[k] &&
            ((i + j + k) % 10) == 3) {
          return true;
        }
      }
    }
  }
  return false;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
4
20 22 19 84
4
1 11 1 2022
4
1100 1100 1100 1111
5
12 34 56 78 90
4
1 9 8 4
6
16 38 94 25 18 99
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
