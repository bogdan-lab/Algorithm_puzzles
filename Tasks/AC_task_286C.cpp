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

int64_t CalcReplaces(const std::string& buff) {
  int count = 0;
  int l = 0;
  int r = buff.size() - 1;
  while (l < r) {
    count += (buff[l] != buff[r]);
    ++l;
    --r;
  }
  return count;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  int64_t a, b;
  input >> a >> b;
  std::string word;
  input >> word;

  if (word.size() == 1) {
    std::cout << "0\n";
    return;
  }

  int64_t min_val = CalcReplaces(word) * b;

  for (int i = 1; i < word.size(); ++i) {
    std::rotate(word.begin(), std::next(word.begin()), word.end());
    min_val = std::min(min_val, i * a + CalcReplaces(word) * b);
  }
  std::cout << min_val << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
