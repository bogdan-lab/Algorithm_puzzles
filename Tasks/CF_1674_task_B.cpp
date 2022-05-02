#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> BuildDictionary() {
  std::vector<std::string> res;
  res.reserve(650);
  for (int ch = static_cast<int>('a'); ch <= static_cast<int>('z'); ++ch) {
    for (int j = static_cast<int>('a'); j <= static_cast<int>('z'); ++j) {
      std::string tmp(2, ch);
      if (j != ch) {
        tmp[1] = j;
        res.push_back(tmp);
      }
    }
  }
  return res;
}

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
  std::vector<std::string> dict = BuildDictionary();
  while (t--) {
    std::string word;
    input >> word;
    auto it = std::lower_bound(dict.begin(), dict.end(), word);
    std::cout << (it - dict.begin()) + 1 << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(7
ab
ac
az
ba
bc
zx
zy
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
