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

void SolveOne(std::istream& input) {
  int n;
  input >> n;

  if (n == 3) {
    std::cout << "NO\n";
    return;
  }

  std::cout << "YES\n";

  if (n & 1) {
    int o_c = (n - 1) / 2;
    int e_c = n - 2 - o_c;

    int ao = -e_c;
    int ae = o_c;
    for (int i = 1; i <= n; ++i) {
      if (i & 1) {
        std::cout << ao << ' ';
      } else {
        std::cout << ae << ' ';
      }
    }
    std::cout << '\n';
  } else {
    int val = 1;
    for (int i = 0; i < n; ++i) {
      std::cout << val << ' ';
      val = -val;
    }
    std::cout << '\n';
  }
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
2
3
4
5
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
