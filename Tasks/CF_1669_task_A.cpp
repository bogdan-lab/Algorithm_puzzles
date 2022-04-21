#include <iostream>
#include <sstream>

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
  while (t--) {
    int rating = 0;
    input >> rating;
    if (rating >= 1900) {
      std::cout << "Division 1\n";
    } else if (rating >= 1600) {
      std::cout << "Division 2\n";
    } else if (rating >= 1400) {
      std::cout << "Division 3\n";
    } else {
      std::cout << "Division 4\n";
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(7
-789
1299
1300
1399
1400
1679
2300
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
