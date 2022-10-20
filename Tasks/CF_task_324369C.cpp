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

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;
  std::vector<std::vector<int64_t>> data(n, std::vector<int64_t>(m));
  std::vector<std::vector<int64_t>> diff = data;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      input >> data[i][j];
    }
  }

  int q;
  input >> q;
  while (q--) {
    int l1, l2, r1, r2;
    int64_t d;
    input >> l1 >> l2 >> r1 >> r2 >> d;
    --l1;
    --l2;
    diff[l1][l2] += d;
    if (r2 < diff[l1].size()) {
      diff[l1][r2] -= d;
    }
    if (r1 < diff.size()) {
      diff[r1][l2] -= d;
    }
    if (r1 < diff.size() && r2 < diff[r1].size()) {
      diff[r1][r2] += d;
    }
  }

  std::vector<std::vector<int64_t>> prefix(n + 1, std::vector<int64_t>(m + 1));
  for (int i = 1; i < prefix.size(); ++i) {
    for (int j = 1; j < prefix[i].size(); ++j) {
      prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] -
                     prefix[i - 1][j - 1] + diff[i - 1][j - 1];
    }
  }

  for (int i = 1; i < prefix.size(); ++i) {
    for (int j = 1; j < prefix[i].size(); ++j) {
      std::cout << prefix[i][j] + data[i - 1][j - 1] << ' ';
    }
    std::cout << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(1 1
10
3
1 1 1 1 100
1 1 1 1 1
1 1 1 1 -3
)";
    Solution(ss);
    std::cout << "expected = 108\n";
  }
  {
    std::stringstream ss;
    ss << R"(2 2
0 0
0 0
3
1 1 2 2 5
1 1 1 2 4
2 1 2 1 -8
)";
    Solution(ss);
    std::cout << "expected = 9 9 -3 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 3
1 2 3
4 5 6
7 8 -9
3
3 3 3 3 18
1 1 3 3 5
1 2 2 3 -2
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
