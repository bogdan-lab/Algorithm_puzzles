#include <algorithm>
#include <iostream>
#include <sstream>

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
  std::string test{"codeforces"};
  while (n--) {
    char c;
    input >> c;
    if (std::find(test.begin(), test.end(), c) == test.end()) {
      std::cout << "NO\n";
    } else {
      std::cout << "YES\n";
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(10
a
b
c
d
e
f
g
h
i
j
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
