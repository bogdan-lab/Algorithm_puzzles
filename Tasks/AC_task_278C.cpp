#include <iostream>
#include <set>
#include <sstream>
#include <utility>

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
  int n, q;
  input >> n >> q;

  std::set<std::pair<int, int>> buff;
  while (q--) {
    int t, a, b;
    input >> t >> a >> b;
    switch (t) {
      case 1: {
        buff.insert({a, b});
        break;
      }
      case 2: {
        buff.erase({a, b});
        break;
      }
      case 3: {
        if (buff.find({a, b}) != buff.end() &&
            buff.find({b, a}) != buff.end()) {
          std::cout << "Yes\n";
        } else {
          std::cout << "No\n";
        }
        break;
      }
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 9
1 1 2
3 1 2
1 2 1
3 1 2
1 2 3
1 3 2
3 1 3
2 1 2
3 1 2
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
