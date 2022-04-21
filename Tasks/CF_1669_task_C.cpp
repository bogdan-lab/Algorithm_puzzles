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
  int t;
  input >> t;
  while (t--) {
    int n = 0;
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    int odd_count = 0;
    for (size_t i = 0; i < data.size(); i += 2) {
      odd_count += data[i] % 2;
    }
    bool can_synch = (odd_count == (data.size() + 1) / 2 || odd_count == 0);

    odd_count = 0;
    for (size_t i = 1; i < data.size(); i += 2) {
      odd_count += data[i] % 2;
    }
    can_synch = can_synch && (odd_count == data.size() / 2 || odd_count == 0);

    std::cout << (can_synch ? "YES\n" : "NO\n");
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
3
1 2 1
4
2 2 2 3
4
2 2 2 2
5
1000 1 1000 1 1000
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
