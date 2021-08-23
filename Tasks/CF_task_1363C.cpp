#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void solution(std::istream& input = std::cin);
void run_tests();

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n, x;
    input >> n >> x;
    Graph g(n);
    for (int i = 0; i < n - 1; ++i) {
      int l, r;
      input >> l >> r;
      g[l - 1].push_back(r - 1);
      g[r - 1].push_back(l - 1);
    }
    if (g[x - 1].size() <= 1) {
      std::cout << "Ayush\n";
      continue;
    }
    int inner = g[x - 1].size();
    int external = n - 1 - inner;
    if (external % 2 && inner % 2) {
      std::cout << "Ashish\n";
    } else if (!(external % 2) && inner % 2) {
      std::cout << "Ayush\n";
    } else if (external % 2 && !(inner % 2)) {
      std::cout << "Ayush\n";
    } else {
      std::cout << "Ashish\n";
    }
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(1
3 1
2 1
3 1
)";
    solution(ss);
    std::cout << "expected = Ashish\n";
  }
  {
    std::stringstream ss;
    ss << R"(1
3 2
1 2
1 3
)";
    solution(ss);
    std::cout << "expected = Ayush\n";
  }
}
