#include <algorithm>
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

void Solution(std::istream& input) {
  int case_num, char_num;
  input >> case_num;
  std::string buff;
  std::string timur = "Timur";
  while (case_num--) {
    input >> char_num >> buff;
    if (buff.size() != timur.size()) {
      std::cout << "NO\n";
      continue;
    }
    bool status = true;
    for (auto ch : timur) {
      auto it = std::find(buff.begin(), buff.end(), ch);
      if (it == buff.end()) {
        status = false;
      }
    }
    if (status) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(10
5
Timur
5
miurT
5
Trumi
5
mriTu
5
timur
4
Timr
6
Timuur
10
codeforces
10
TimurTimur
5
TIMUR
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
