#include <iostream>
#include <sstream>
#include <vector>

int Left(int i) { return 2 * i + 1; }
int Right(int i) { return 2 * i + 2; }

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

bool Check(int a, int b, int max_val) {
  if (a > b) return false;
  if (a > max_val || b > max_val) return false;
  return Left(a) == b || Right(a) == b;
}

void Solution(std::istream& input) {
  int a, b;
  input >> a >> b;
  --a;
  --b;
  if (Check(a, b, 14)) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
