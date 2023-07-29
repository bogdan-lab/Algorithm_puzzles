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

bool CanSellFor(int x, int own_price) { return own_price <= x; }

bool CanBuyFor(int x, int own_price) { return own_price >= x; }

int CountSellers(int x, const std::vector<int>& prices) {
  int res = 0;
  for (const auto& el : prices) {
    if (CanSellFor(x, el)) {
      ++res;
    }
  }
  return res;
}

int CountBuyers(int x, const std::vector<int>& prices) {
  int res = 0;
  for (const auto& el : prices) {
    if (CanBuyFor(x, el)) {
      ++res;
    }
  }
  return res;
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;

  std::vector<int> sellers(n);
  for (auto& el : sellers) {
    input >> el;
  }

  std::vector<int> buyers(m);
  for (auto& el : buyers) {
    input >> el;
  }

  int l = 0;
  int r = 1'000'000'000 + 1;
  while (r - l > 1) {
    int m = (l + r) / 2;
    int b = CountBuyers(m, buyers);
    int s = CountSellers(m, sellers);
    if (s >= b) {
      r = m;
    } else {
      l = m;
    }
  }

  std::cout << r << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
