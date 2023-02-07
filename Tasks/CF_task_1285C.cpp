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

std::vector<int64_t> Factorize(int64_t x) {
  std::vector<int64_t> res;
  int64_t p = 2;
  int64_t prev = 2;
  while (x >= p * p) {
    if ((x % p) == 0) {
      x /= p;
      if (res.empty() || prev != p) {
        res.push_back(1);
      }
      res.back() *= p;
    } else {
      prev = p;
      ++p;
    }
  }
  if (x == 1) return res;
  if (res.empty() || x != prev) {
    res.push_back(1);
  }
  res.back() *= x;
  return res;
}

bool PairIsSmaller(std::pair<int64_t, int64_t> l,
                   std::pair<int64_t, int64_t> r) {
  return std::max(l.first, l.second) < std::max(r.first, r.second);
}

std::pair<int64_t, int64_t> FindPair(const std::vector<int64_t>& data) {
  std::pair<int64_t, int64_t> res{1, 1};
  for (const auto& el : data) {
    if (res.first > res.second) {
      res.second *= el;
    } else {
      res.first *= el;
    }
  }
  return res;
}

void Solution(std::istream& input) {
  int64_t x;
  input >> x;
  std::vector<int64_t> val_to_count = Factorize(x);
  std::pair<int64_t, int64_t> res = FindPair(val_to_count);
  std::cout << res.first << " " << res.second << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
