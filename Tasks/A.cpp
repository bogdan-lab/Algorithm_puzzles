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
  int t = 0;
  input >> t;
  while (t--) {
    std::vector<int> data(7);
    for (auto& el : data) {
      input >> el;
    }
    int a = data[0];
    int b = data[1];
    int c = data[2] == data[0] + data[1] ? data[3] : data[2];
    std::cout << a << ' ' << b << ' ' << c << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
1 3 4 4 5 7 8
1 2 3 4 5 6 7
300000000 300000000 300000000 600000000 600000000 600000000 900000000
1 1 2 999999998 999999999 999999999 1000000000
1 2 2 3 3 4 5
)";
    Solution(ss);
  }
}
