#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int64_t> GetPrefixCount(int a, int b);
int64_t CountForRightEdge(const std::vector<int64_t>& prefix, int64_t edge);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int64_t t;
  input >> t;
  while (t--) {
    int64_t a, b, q;
    input >> a >> b >> q;
    std::vector<int64_t> prefix = GetPrefixCount(a, b);

    std::vector<int64_t> answer;
    answer.reserve(q);
    while (q--) {
      int64_t l, r;
      input >> l >> r;
      answer.push_back(CountForRightEdge(prefix, r) -
                       CountForRightEdge(prefix, l - 1));
    }
    for (const auto& el : answer) {
      std::cout << el << ' ';
    }
    std::cout << '\n';
  }
}

bool ConditionCheck(int64_t x, int64_t a, int64_t b) {
  return (x % a) % b != (x % b) % a;
}

std::vector<int64_t> GetPrefixCount(int a, int b) {
  std::vector<int64_t> result(a * b);
  for (size_t i = 0; i < a * b; ++i) {
    result[i] = ConditionCheck(i, a, b) ? 1 : 0;
  }
  for (size_t i = 1; i < result.size(); ++i) {
    result[i] += result[i - 1];
  }
  return result;
}

int64_t CountForRightEdge(const std::vector<int64_t>& prefix, int64_t edge) {
  int64_t count_full = edge / prefix.size() * prefix.back();
  int64_t length = edge % prefix.size();
  return count_full + prefix[length];
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
4 6 5
1 1
1 3
1 5
1 7
1 9
7 10 2
7 8
100 200
)";
    Solution(ss);
    std::cout << "expected = 0 0 0 2 4 || 0 91\n";
  }
}
