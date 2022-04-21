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
  int t;
  input >> t;
  while (t--) {
    int n = 0;
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    int found_val = -1;
    std::vector<int> count_arr(n);
    for (const auto& val : data) {
      count_arr[val - 1] += 1;
      if (count_arr[val - 1] == 3) {
        found_val = val;
        break;
      }
    }
    std::cout << found_val << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(7
1
1
3
2 2 2
7
2 2 3 3 4 2 2
8
1 4 3 4 3 2 4 1
9
1 1 1 2 2 2 3 3 3
5
1 5 2 4 3
4
4 4 4 4
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
