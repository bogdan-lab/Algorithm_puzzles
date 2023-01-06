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
  std::vector<int> a(n);
  for (auto& el : a) input >> el;
  std::vector<int> b(n);
  for (auto& el : b) input >> el;

  std::vector<int> diff(n);
  for (int i = 0; i < n; ++i) {
    diff[i] = a[i] - b[i];
  }

  std::sort(diff.begin(), diff.end());

  int64_t count = 0;
  for (int i = 0; i < diff.size(); ++i) {
    if (diff[i] <= 0) {
      auto it = std::upper_bound(diff.begin(), diff.end(), -diff[i]);
      count += diff.end() - it;

    } else {
      count += diff.size() - i - 1;
    }
  }
  std::cout << count << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
4 8 2 6 2
4 5 4 1 3
)";
    Solution(ss);
    std::cout << "expected = 7\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
1 3 2 4
1 3 2 4
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
