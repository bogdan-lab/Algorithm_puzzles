#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

constexpr uint64_t kEmptySum = 0;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::vector<uint64_t> GetElements(const std::vector<uint64_t>& data,
                                  uint16_t st) {
  std::vector<uint64_t> res;
  int i = 0;
  while (st > 0) {
    assert(i < data.size());
    if (st & 1) {
      res.push_back(data[i]);
    }
    ++i;
    st >>= 1;
  }
  return res;
}

uint64_t GetSum(const std::vector<uint64_t>& data, uint16_t st, int x) {
  std::vector<uint64_t> elements = GetElements(data, st);
  if (elements.size() == 1) return kEmptySum;
  if (elements.back() - elements.front() < x) return kEmptySum;
  return std::accumulate(elements.begin(), elements.end(), 0ULL);
}

uint16_t GetTotalNumber(int n) {
  uint16_t res = 0;
  while (true) {
    res += 1;
    --n;
    if (n == 0) break;
    res <<= 1;
  }
  return res;
}

uint64_t GetNumber(const std::vector<uint64_t>& data, uint64_t l, uint64_t r,
                   uint64_t x) {
  uint32_t total_num = GetTotalNumber(data.size());
  std::vector<uint64_t> sums(total_num + 1, kEmptySum);
  for (uint32_t i = 1; i <= total_num; ++i) {
    sums[i] = GetSum(data, i, x);
  }
  return std::count_if(sums.begin(), sums.end(), [&](uint64_t val) {
    return val != kEmptySum && val >= l && val <= r;
  });
}

void Solution(std::istream& input) {
  int n, l, r, x;
  input >> n >> l >> r >> x;
  std::vector<uint64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }
  std::sort(data.begin(), data.end());
  std::cout << GetNumber(data, l, r, x) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 5 6 1
1 2 3
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
