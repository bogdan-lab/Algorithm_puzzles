#include <iostream>
#include <sstream>
#include <string>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

bool Merge(const std::string& lhs, const std::string& rhs) {
  for (size_t i = 0; i < lhs.size(); ++i) {
    if (lhs[i] != rhs[i] && !((lhs[i] == 'G' && rhs[i] == 'B') ||
                              (lhs[i] == 'B' && rhs[i] == 'G'))) {
      return false;
    }
  }
  return true;
}

void Solution(std::istream& input) {
  int case_num, row_len;
  input >> case_num;
  std::string lhs, rhs;
  while (case_num--) {
    input >> row_len >> lhs >> rhs;
    if (Merge(lhs, rhs)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
2
RG
RB
4
GRBG
GBGB
5
GGGGG
BBBBB
7
BBBBBBB
RRRRRRR
8
RGBRRGBR
RGGRRBGR
1
G
G
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
