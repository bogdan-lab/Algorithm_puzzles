#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
std::vector<std::string> PerformFall(const std::vector<std::string>& data);

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
    int r_n, c_n;
    input >> r_n >> c_n;
    std::vector<std::string> data(r_n);
    for (auto& el : data) {
      input >> el;
    }
    std::vector<std::string> result = PerformFall(data);
    for (const auto& el : result) {
      std::cout << el << '\n';
    }
    // std::cout << "\n====================\n";
  }
}

std::vector<std::string> PerformFall(const std::vector<std::string>& data) {
  std::vector<std::string> res = data;
  if (data.size() <= 1) return res;
  for (int col = 0; col < data.front().size(); ++col) {
    int row = data.size() - 1;
    while (row >= 0 && res[row][col] != '.') {
      row--;
    }
    int last_empty_index = row;
    row--;
    while (row >= 0) {
      if (res[row][col] == '*') {
        std::swap(res[row][col], res[last_empty_index][col]);
        last_empty_index--;
        row--;
      } else if (res[row][col] == 'o') {
        while (row >= 0 && res[row][col] != '.') {
          row--;
        }
        last_empty_index = row;
      } else {
        row--;
      }
    }
  }
  return res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
6 10
.*.*....*.
.*.......*
...o....o.
.*.*....*.
..........
.o......o*
2 9
...***ooo
.*o.*o.*o
5 5
*****
*....
*****
....*
*****
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
