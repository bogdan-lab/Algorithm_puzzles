#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int> MakeZArray(const std::string& text);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::string text;
  input >> text;

  std::vector<int> z = MakeZArray(text);
  for (int i = 1; i < z.size(); ++i) {
    std::cout << z[i] << ' ';
  }
  std::cout << '\n';
}

std::vector<int> MakeZArray(const std::string& text) {
  std::vector<int> z(text.size());
  int x = 0;
  int y = 0;
  for (int i = 1; i < text.size(); ++i) {
    z[i] = std::max(0, std::min(z[i - x], y - i + 1));
    while (i + z[i] < text.size() && text[z[i]] == text[i + z[i]]) {
      x = i;
      y = i + z[i];
      z[i]++;
    }
  }
  return z;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(aaaAAA
)";
    Solution(ss);
    std::cout << "expected = 2 1 0 0 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(abacaba
)";
    Solution(ss);
    std::cout << "expected = 0 1 0 3 0 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(acbacdacbacbacda
)";
    Solution(ss);
    std::cout << "expected = 0 0 2 0 0 5 0 0 7 0 0 2 0 0 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(abcde
)";
    Solution(ss);
    std::cout << "expected = 0 0 0 0\n";
  }
}
