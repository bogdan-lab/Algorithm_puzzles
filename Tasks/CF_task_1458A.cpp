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

int64_t GCD(int64_t l, int64_t r) {
  if (l > r) std::swap(l, r);
  while (l) {
    r %= l;
    std::swap(l, r);
  }
  return r;
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;
  std::vector<int64_t> a(n);
  for (auto& el : a) input >> el;
  std::vector<int64_t> b(m);
  for (auto& el : b) input >> el;

  if (n == 1) {
    for (int i = 0; i < m; ++i) {
      std::cout << a[0] + b[i] << ' ';
    }
    std::cout << '\n';
    return;
  }

  std::sort(a.begin(), a.end());

  std::vector<int64_t> diff;
  diff.reserve(a.size() - 1);
  for (int i = 1; i < a.size(); ++i) {
    diff.push_back(a[i] - a[i - 1]);
  }

  int64_t diff_gcd = diff[0];
  for (const auto& el : diff) diff_gcd = GCD(diff_gcd, el);

  for (int i = 0; i < b.size(); ++i) {
    std::cout << GCD(a[0] + b[i], diff_gcd) << ' ';
  }
  std::cout << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4 4
1 25 121 169
1 2 7 23
)";
    Solution(ss);
    std::cout << "expected = 2; 3; 8; 24\n";
  }
}
