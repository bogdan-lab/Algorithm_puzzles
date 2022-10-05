#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

constexpr int kMaxValue = 1'000'000;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<int> res(n);
  res[0] = data[0] == 1 ? 0 : 1;
  for (int i = 1; i < data.size(); ++i) {
    if (data[i] == data[i - 1]) {
      res[i] = i + 1;
    } else {
      res[i] = data[i - 1];
      if (res[data[i] - 1] == data[i]) {
        res[data[i] - 1] = data[i] + 1;
      }
    }
  }

  std::vector<int> lookup(100'000 + 10);
  lookup[res[0]] = 1;
  auto it =
      std::find_if(lookup.begin(), lookup.end(), [](int v) { return v == 0; });
  for (int i = 1; i < data.size(); ++i) {
    lookup[res[i]] = 1;
    it = std::find_if(it, lookup.end(), [](int v) { return v == 0; });
    if (data[i] != it - lookup.begin()) {
      std::cout << "-1\n";
      return;
    }
  }

  for (const auto& el : res) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
1 2 3
)";
    Solution(ss);
    std::cout << "expected = 0; 1; 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
0 0 0 2
)";
    Solution(ss);
    std::cout << "expected = 1; 3; 4; 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
1 1 3
)";
    Solution(ss);
    std::cout << "expected = 0; 2; 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(7
0 0 2 2 5 5 6
)";
    Solution(ss);
    std::cout << "expected = 1; 3; 0; 4; 2; 7; 5\n";
  }
}
