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
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      input >> data[i][j];
    }
  }

  std::vector<std::vector<int64_t>> prefix(n + 1, std::vector<int64_t>(m + 1));
  for (int i = 1; i < prefix.size(); ++i) {
    for (int j = 1; j < prefix[i].size(); ++j) {
      prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] -
                     prefix[i - 1][j - 1] + data[i - 1][j - 1];
    }
  }

  int q;
  input >> q;
  while (q--) {
    int lx, ly, rx, ry;
    input >> lx >> ly >> rx >> ry;
    --lx;
    --ly;
    std::cout << prefix[rx][ry] - prefix[lx][ry] - prefix[rx][ly] +
                     prefix[lx][ly]
              << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
