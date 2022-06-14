#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

bool CheckSum(const std::vector<int>& data);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
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
  if (rem[1] >= 3) return true;
  if (rem[2] >= 1 && rem[0] >= 1 && rem[1] >= 1) return true;
  if (rem[0] >= 2 && rem[3] >= 1) return true;
  if (rem[7] >= 1 && rem[3] >= 2) return true;
  if (rem[8] >= 1 && rem[2] >= 1 && rem[3] >= 1) return true;
  if (rem[9] >= 1 && rem[1] >= 1 && rem[3] >= 3) return true;
  if (rem[7] >= 1 && rem[4] >= 1 && rem[2] >= 1) return true;
  if (rem[6] >= 1 && rem[4] >= 1 && rem[3] >= 1) return true;
  if (rem[5] >= 1 && rem[5] >= 1 && rem[3] >= 1) return true;
  if (rem[8] >= 1 && rem[3] >= 1 && rem[2] >= 1) return true;
  if (rem[9] >= 1 && rem[2] >= 1 && rem[2] >= 1) return true;
  if (rem[8] >= 1 && rem[4] >= 1 && rem[1] >= 1) return true;
  if (rem[9] >= 1 && rem[3] >= 1 && rem[1] >= 1) return true;
  if (rem[9] >= 1 && rem[4] >= 1 && rem[0] >= 1) return true;
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
