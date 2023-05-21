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

uint64_t GetLargerGift(const std::vector<uint64_t>& data, uint64_t val,
                       uint64_t d) {
  auto it = std::upper_bound(data.begin(), data.end(), val + d);
  if (it == data.begin()) return 0;
  uint64_t res = *std::prev(it);
  uint64_t diff = res >= val ? res - val : val - res;
  return diff <= d ? res : 0;
}

std::vector<uint64_t> GetPossibleSums(std::vector<uint64_t>& a,
                                      std::vector<uint64_t>& b, uint64_t d) {
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());

  std::vector<uint64_t> res;

  for (const auto& el : a) {
    uint64_t larger = GetLargerGift(b, el, d);
    if (larger) {
      res.push_back(larger + el);
    }
  }

  for (const auto& el : b) {
    uint64_t larger = GetLargerGift(a, el, d);
    if (larger) {
      res.push_back(larger + el);
    }
  }

  return res;
}

void Solution(std::istream& input) {
  int n, m;
  uint64_t d;
  input >> n >> m >> d;
  std::vector<uint64_t> a(n);
  for (auto& el : a) {
    input >> el;
  }
  std::vector<uint64_t> b(m);
  for (auto& el : b) {
    input >> el;
  }

  std::vector<uint64_t> var = GetPossibleSums(a, b, d);
  if (var.empty()) {
    std::cout << "-1\n";
    return;
  }
  std::cout << *std::max_element(var.begin(), var.end()) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(8 6 1
2 5 6 5 2 1 7 9
7 2 5 5 2 4
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
