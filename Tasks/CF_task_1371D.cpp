#include <iostream>
#include <sstream>
#include <vector>

struct Result {
  Result(int n) : table(n, std::vector<int>(n)) {}

  int f = 0;
  std::vector<std::vector<int>> table;
};

Result BuildTable(int n, int k);

void WriteToTable(std::vector<std::vector<int>>& data, int i, int level,
                  int value);

void Solution(std::istream& input = std::cin);
void RunTests();

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
  int n, k;
  while (t--) {
    input >> n >> k;
    Result res = BuildTable(n, k);
    std::cout << res.f << '\n';
    for (const auto& out : res.table) {
      for (const auto& el : out) {
        std::cout << el;
      }
      std::cout << '\n';
    }
  }
}

void WriteToTable(std::vector<std::vector<int>>& data, int i, int level,
                  int value) {
  int row = i - level;
  if (row < 0) {
    row += data.size();
  }
  data[row][i] = value;
}

Result BuildTable(int n, int k) {
  Result res(n);
  int level = 0;
  int i = 0;
  while (k--) {
    WriteToTable(res.table, i++, level, 1);
    if (i == n) {
      i = 0;
      ++level;
    }
  }
  res.f = i ? 2 : 0;
  return res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
2 2
3 8
1 0
4 16
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
