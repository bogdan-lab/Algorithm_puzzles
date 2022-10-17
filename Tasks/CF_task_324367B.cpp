#include <iostream>
#include <sstream>
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
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<int64_t> prefix(data.size() + 1);
  for (int i = 1; i < prefix.size(); ++i) {
    prefix[i] = prefix[i - 1] ^ data[i - 1];
  }

  int q;
  input >> q;
  while (q--) {
    int l, r;
    input >> l >> r;
    --l;
    std::cout << (prefix[l] ^ prefix[r]) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
12 6
3
1 1
2 2
1 2
)";
    Solution(ss);
    std::cout << "expected = 12; 6; 10\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
1 2 3 0 4
5
1 5
1 2
4 4
3 4
2 5
)";
    Solution(ss);
    std::cout << "expected = 4; 3; 0; 3; 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(7
1 1 1 1 1 1 1
9
1 7
2 6
3 4
2 5
5 7
6 6
3 3
2 7
1 1
)";
    Solution(ss);
    std::cout << "expected = 1 1 0 0 1 1 1 0 1\n";
  }
}
