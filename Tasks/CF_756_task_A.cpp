#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

void Solution(std::istream& input = std::cin);
void RunTests();
int SolveOne(const std::string& str);
bool CheckIfEven(char c);

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
  while (t--) {
    std::string str;
    input >> str;
    std::cout << SolveOne(str) << '\n';
  }
}

int SolveOne(const std::string& str) {
  if (str.empty()) return -1;
  if (CheckIfEven(str.back())) return 0;
  if (CheckIfEven(str.front())) return 1;
  auto it = std::find_if(str.begin(), str.end(), CheckIfEven);
  if (it == str.end()) return -1;
  return 2;
}

bool CheckIfEven(char c) {
  return !((static_cast<int>(c) - static_cast<int>('0')) % 2);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
3876
387
4489
3
    )";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
