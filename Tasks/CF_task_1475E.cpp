#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

constexpr int64_t kMod = 1'000'000'007;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int64_t GetFactorial(int64_t val) {
  int64_t res = 1;
  for (int64_t v = 2; v <= val; ++v) {
    res = (res * v) % kMod;
  }
  return res;
}

uint64_t GetNumber(std::vector<int64_t>& data, int k) {
  std::sort(data.begin(), data.end());
  int64_t max_sum = std::accumulate(data.end() - k, data.end(), 0LL);

  int i = data.size() - k;
  int eq_val = data[i];
  int64_t all_dup_num = std::count(data.begin(), data.end(), eq_val);
  int64_t vac_places = std::count(data.begin() + i, data.end(), eq_val);
  int64_t tmp =
      (GetFactorial(vac_places) * GetFactorial(all_dup_num - vac_places)) %
      kMod;
  return (GetFactorial(all_dup_num) / tmp) % kMod;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n, k;
    input >> n >> k;
    std::vector<int64_t> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::cout << GetNumber(data, k) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
4 3
1 3 1 2
4 2
1 1 1 1
2 1
1 2
4
1 5 5 5
)";
    Solution(ss);
    std::cout << "expected = 2; 6; 1; 3\n";
  }
}
