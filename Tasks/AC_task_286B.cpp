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
  int n;
  input >> n;
  std::string buff;
  input >> buff;

  std::string res;
  res.reserve(buff.size());
  for (int i = 0; i < buff.size(); ++i) {
    res.push_back(buff[i]);
    if (i + 1 < buff.size() && buff[i] == 'n' && buff[i + 1] == 'a') {
      res.push_back('y');
    }
  }
  std::cout << res << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
