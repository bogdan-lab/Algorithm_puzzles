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

char Compare(const std::string& a, const std::string& b) {
  if (a.back() < b.back()) return '>';
  if (a.back() > b.back()) return '<';

  switch (a.back()) {
    case 'S': {
      if (a.size() < b.size()) return '>';
      if (a.size() > b.size()) return '<';
      return '=';
    }
    case 'L': {
      if (a.size() < b.size()) return '<';
      if (a.size() > b.size()) return '>';
      return '=';
    }
  }
  return '=';
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  std::string a;
  std::string b;
  while (t--) {
    input >> a >> b;
    std::cout << Compare(a, b) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
XXXS XS
XXXL XL
XL M
XXL XXL
XXXXXS M
L M
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
