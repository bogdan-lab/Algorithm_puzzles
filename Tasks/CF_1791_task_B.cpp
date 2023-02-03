#include <iostream>
#include <sstream>
#include <string>
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

bool FindCandy(const std::string& data) {
  int x = 0;
  int y = 0;
  for (const auto& el : data) {
    switch (el) {
      case 'U': {
        ++y;
        break;
      }
      case 'R': {
        ++x;
        break;
      }
      case 'D': {
        --y;
        break;
      }
      case 'L': {
        --x;
        break;
      }
      default:
        break;
    }
    if (x == 1 && y == 1) return true;
  }
  return false;
}

void SolveOne(std::istream& input) {
  int n;
  std::string path;
  input >> n >> path;
  if (FindCandy(path)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(7
7
UUURDDL
2
UR
8
RRRUUDDD
3
LLL
4
DUUR
5
RUDLL
11
LLLLDDRUDRD
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
