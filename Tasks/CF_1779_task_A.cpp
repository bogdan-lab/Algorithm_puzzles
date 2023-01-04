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

void SolveOne(std::istream& input) {
  int n;
  input >> n;
  std::string lamps;
  input >> lamps;

  int l_count = std::count(lamps.begin(), lamps.end(), 'L');
  int r_count = std::count(lamps.begin(), lamps.end(), 'R');
  if (l_count == 0 || r_count == 0) {
    std::cout << "-1\n";
    return;
  }

  char prev = lamps[0];
  for (int i = 1; i < lamps.size(); ++i) {
    char curr = lamps[i];
    if (prev == 'R' && curr == 'L') {
      std::cout << "0\n";
      return;
    }
    prev = curr;
  }

  prev = lamps[0];
  for (int i = 1; i < lamps.size(); ++i) {
    char curr = lamps[i];
    if (prev == 'L' && curr == 'R') {
      std::cout << i << '\n';
      return;
    }
    prev = curr;
  }
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
2
LL
2
LR
2
RL
2
RR
7
LLRLLLR
7
RRLRRRL
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
