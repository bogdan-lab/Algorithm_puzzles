#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

constexpr size_t kMaxVal = 2 * 1000'000'000 + 1;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::vector<int> BuildLookup(int n) {
  auto res = std::make_unique<std::bitset<kMaxVal>>();
  res->set();
  res->reset(0);
  res->reset(1);
  std::vector<int> coll;
  for (int i = 2; i <= n; ++i) {
    if (!res->test(i)) continue;
    coll.push_back(i);
    int64_t j = 2 * i;
    while (j <= n) {
      res->reset(j);
      j += i;
    }
  }

  return coll;
}

int CalcTax(const std::vector<int>& primes, int val) {
  auto bnd_it = std::lower_bound(primes.begin(), primes.end(), val);
  if (bnd_it != primes.end() && *bnd_it == val) {
    return 1;
  }
  assert(bnd_it != primes.begin());
  --bnd_it;
  // here bnd_it is first on the left from val
  if (*bnd_it == val - 1) {
    --bnd_it;
  }
  return 1 + CalcTax(primes, val - *bnd_it);
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> primes = BuildLookup(n);
  std::cout << CalcTax(primes, n) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(27
    )";
    Solution(ss);
    std::cout << "expected = 3\n";
  }
}
