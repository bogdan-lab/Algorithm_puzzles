#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

int64_t CalcPermutations(const std::string& s, const std::string& t);

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
  int q;
  input >> q;
  while (q--) {
    std::string s, t;
    input >> s >> t;
    std::cout << CalcPermutations(s, t) << '\n';
  }
}

int64_t CalcPermutations(const std::string& s, const std::string& t) {
  int a_count = std::count(t.begin(), t.end(), 'a');
  if (a_count != 0) {
    if (a_count == 1 && t.size() == 1) {
      return 1;
    }
    return -1;
  }
  int64_t max_n = s.size();
  int64_t cur_val = 1;
  while (--max_n) {
    cur_val = 2 * cur_val + 1;
  }
  return cur_val + 1;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
aaaa
a
aa
abc
a
b
aaaa
b
aaa
b
)";
    Solution(ss);
    std::cout << "expected = 1; -1; 2; 16; 8\n";
  }
}
