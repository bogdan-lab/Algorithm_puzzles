#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int CountSubArrays(const std::vector<int>& data, int window);

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
    int n, k;
    input >> n >> k;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::cout << CountSubArrays(data, k + 1) << '\n';
  }
}

int CountSubArrays(const std::vector<int>& data, int window) {
  int curr_size = 0;
  for (int i = 1; i < window; ++i) {
    curr_size += (data[i - 1] < 2 * data[i]);
  }
  int match_size = window - 1;
  int count = (curr_size == match_size);
  for (int i = window; i < data.size(); ++i) {
    curr_size -= (data[i - window] < 2 * data[i - window + 1]);
    curr_size += (data[i - 1] < 2 * data[i]);
    count += (curr_size == match_size);
  }
  return count;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
4 2
20 22 19 84
5 1
9 5 3 2 1
5 2
9 5 3 2 1
7 2
22 12 16 4 3 22 12
7 3
22 12 16 4 3 22 12
9 3
3 9 12 3 9 12 3 9 12
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
