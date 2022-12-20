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

void Solution(std::istream& input) {
  int n;
  input >> n;

  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::sort(data.begin(), data.end());
  int r = data.size() / 2;
  int count = 0;
  std::vector<int> lookup(data.size());
  for (int l = 0; l < data.size(); ++l) {
    if (lookup[l]) continue;
    int val = data[l];
    while (r < data.size() && data[r] < 2 * val) {
      ++r;
    }
    if (r == data.size()) break;
    ++count;
    lookup[l] = 1;
    lookup[r] = 1;
    ++r;  // we have picked th r value
  }

  std::cout << data.size() - count << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(8
2
5
7
6
9
8
4
2
)";
    Solution(ss);
    std::cout << "expected = 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(8
9
1
6
2
6
5
8
3
)";
    Solution(ss);
    std::cout << "expected = 5\n";
  }
}

// 2 5 7 6 9 8 4 2
// 2 2 4 5 6 7 8 9
//

