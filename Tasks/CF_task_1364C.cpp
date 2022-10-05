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

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<int> lookup(100'002, -1);
  std::vector<int> res(n);
  int curr_max = 0;
  if (data[0] == 1) {
    res[0] = 0;
    lookup[0] = 0;
    curr_max = 1;
  } else {
    res[0] = 1;
    lookup[1] = 0;
    curr_max = 2;
  }

  for (int i = 1; i < res.size(); ++i) {
    if (curr_max == data[i]) {
      ++curr_max;
    }
    if (data[i] > data[i - 1]) {
      if (lookup[data[i]] != -1) {
        res[lookup[data[i]]] = curr_max;
        lookup[curr_max] = lookup[data[i]];
        lookup[data[i]] = -1;
        ++curr_max;
      }
      res[i] = data[i - 1];
      lookup[data[i - 1]] = i;
      curr_max = std::max(curr_max, data[i - 1] + 1);
    } else {
      res[i] = curr_max;
      lookup[curr_max] = i;
      ++curr_max;
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
