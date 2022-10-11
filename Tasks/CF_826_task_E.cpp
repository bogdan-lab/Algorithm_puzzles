#include <iostream>
#include <sstream>
#include <string>
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

std::string GetAnswer(const std::vector<int>& data) {
  std::vector<int> lookup(data.size());
  for (int i = 0; i < data.size(); ++i) {
    if (i - data[i] == 0 || (i - data[i] > 0 && lookup[i - data[i] - 1])) {
      lookup[i] = 1;
    }
    if (i + data[i] < data.size() && (i == 0 || lookup[i - 1])) {
      lookup[i + data[i]] = 1;
    }
  }
  return lookup.back() ? "YES" : "NO";
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }

    std::cout << GetAnswer(data) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(7
9
1 1 2 3 1 3 2 2 3
5
12 1 2 7 5
6
5 7 8 9 10 3
4
4 8 6 2
2
3 1
10
4 6 2 1 9 4 9 3 4 2
1
1
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
