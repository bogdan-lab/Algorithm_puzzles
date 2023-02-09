#include <algorithm>
#include <iostream>
#include <sstream>
#include <utility>
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

int GCD(int l, int r) {
  if (r < l) std::swap(l, r);
  while (l) {
    r %= l;
    std::swap(l, r);
  }
  return r;
}

std::pair<int, int> Adjust(const std::pair<int, int>& p, int x0, int y0) {
  int x_dif = p.first - x0;
  int y_dif = p.second - y0;
  int gcd = GCD(std::abs(x_dif), std::abs(y_dif));
  int mult = y_dif < 0 ? -1 : 1;
  return {mult * x_dif / gcd, mult * y_dif / gcd};
}

int CountUnique(const std::vector<std::pair<int, int>>& data) {
  if (data.empty()) return 0;
  int count = 1;
  for (int i = 1; i < data.size(); ++i) {
    if (data[i] > data[i - 1]) {
      ++count;
    }
  }
  return count;
}

void Solution(std::istream& input) {
  int n, x0, y0;
  input >> n >> x0 >> y0;
  std::vector<std::pair<int, int>> data(n);
  for (auto& el : data) {
    input >> el.first >> el.second;
  }

  int count = 0;
  // Count with same x or y.
  auto it =
      std::remove_if(data.begin(), data.end(),
                     [&](std::pair<int, int> p) { return p.first == x0; });
  count += (it != data.end());
  data.erase(it, data.end());
  it = std::remove_if(data.begin(), data.end(),
                      [&](std::pair<int, int> p) { return p.second == y0; });
  count += (it != data.end());
  data.erase(it, data.end());

  for (auto& el : data) {
    el = Adjust(el, x0, y0);
  }

  std::sort(data.begin(), data.end());
  count += CountUnique(data);

  std::cout << count << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2 1 2
1 1
1 0
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
