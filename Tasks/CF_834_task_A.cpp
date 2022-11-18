#include <algorithm>
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

bool Check(const std::string& yes, const std::string& s) {
  int i = 0;
  if (s.front() != 'Y') {
    int j = std::find(yes.begin(), yes.end(), s.front()) - yes.begin();
    if (j == yes.size()) return false;
    while (j < yes.size() && i < s.size()) {
      if (s[i] != yes[j]) return false;
      ++i;
      ++j;
    }
  }
  int j = 0;
  while (i < s.size()) {
    if (s[i] != yes[j % yes.size()]) return false;
    ++i;
    ++j;
  }
  return true;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  std::string yes = "Yes";
  while (t--) {
    std::string s;
    input >> s;
    if (Check(yes, s)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(12
YES
esYes
codeforces
es
se
YesY
esYesYesYesYesYesYe
seY
Yess
sY
o
Yes
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
