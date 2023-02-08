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

bool CanPartition(const std::vector<int>& prefix,
                  const std::vector<int>& suffix) {
  for (int i = 1; i < suffix.size(); ++i) {
    if (prefix[i - 1] > suffix[i]) {
      return true;
    }
  }
  return false;
}

void SolveOne(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<int> prefix(data.size());  // inclusive
  prefix.front() = data.front();
  for (int i = 1; i < data.size(); ++i) {
    prefix[i] = std::min(prefix[i - 1], data[i]);
  }
  std::vector<int> suffix(data.size());  // inclusive
  suffix.back() = data.back();
  for (int i = data.size() - 2; i >= 0; --i) {
    suffix[i] = std::max(suffix[i + 1], data[i]);
  }

  if (CanPartition(prefix, suffix)) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
  }
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
3
1 2 3
4
3 1 2 4
3
2 3 1
6
2 4 6 1 3 5
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
