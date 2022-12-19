#include <algorithm>
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

void SolveTest(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  int curr_lvl_free = 0;
  int prev_lvl_free = 1;
  int index = 1;
  int depth = 0;
  bool next_layer_start = true;
  while (index < data.size()) {
    int start = index;
    ++index;
    while (index < data.size() && data[index] > data[index - 1]) {
      ++index;
    }
    curr_lvl_free += index - start;
    if (next_layer_start) {
      next_layer_start = false;
      ++depth;
    }
    --prev_lvl_free;
    if (!prev_lvl_free) {
      std::swap(prev_lvl_free, curr_lvl_free);
      next_layer_start = true;
    }
  }

  std::cout << depth << '\n';
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    SolveTest(input);
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
4
1 4 3 2
2
1 2
3
1 2 3
)";
    Solution(ss);
    std::cout << "expected = 3; 1; 1\n";
  }
}
