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

int Sort(std::vector<int>& data, int w_size, int count) {
  for (int i = 0; i <= data.size() - 2 * w_size; i += 2 * w_size) {
    int first_1 = data[i];
    int last_2 = data[i + 2 * w_size - 1];
    if (first_1 < last_2 && last_2 - first_1 == 2 * w_size - 1) {
      // everything is fine
    } else if (first_1 > last_2 && first_1 - last_2 == 1) {
      ++count;
      std::swap_ranges(data.begin() + i, data.begin() + i + w_size,
                       data.begin() + i + w_size);
    } else {
      return -1;
    }
  }

  return count;
}

int CountSteps(std::vector<int>& data) {
  int w_size = 1;
  int count = 0;
  while (w_size < data.size()) {
    count = Sort(data, w_size, count);
    if (count == -1) break;
    w_size *= 2;
  }
  return count;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int m;
    input >> m;
    std::vector<int> data(m);
    for (auto& el : data) {
      input >> el;
    }

    std::cout << CountSteps(data) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
8
6 5 7 8 4 3 1 2
4
3 1 4 2
1
1
8
7 8 4 3 1 2 6 5
4
4 3 2 1
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
