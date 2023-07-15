#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
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
  int n;
  input >> n;
  std::vector<std::string> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::unordered_set<std::string> buff;
  for (auto& el : data) {
    auto it = buff.find(el);
    if (it != buff.end()) continue;
    std::reverse(el.begin(), el.end());
    it = buff.find(el);
    if (it != buff.end()) continue;
    buff.insert(el);
  }

  std::cout << buff.size() << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
