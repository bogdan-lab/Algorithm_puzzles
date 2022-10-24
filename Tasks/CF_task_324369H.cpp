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
  int q;
  input >> q;
  std::vector<int> diff(data.size());
  while (q--) {
    int k, x;
    input >> k >> x;
    diff[diff.size() - k] += x;
  }

  std::vector<int64_t> prefix(diff.size() + 1);
  for (int i = 1; i < prefix.size(); ++i) {
    prefix[i] = prefix[i - 1] + diff[i - 1];
  }

  for (int i = 0; i < data.size(); ++i) {
    data[i] += prefix[i + 1];
    std::cout << data[i] << ' ';
  }
  std::cout << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
1000 2000 3000
2
2 2000
1 3000
)";
    Solution(ss);
    std::cout << "expected = 1000 4000 8000\n";
  }
}
