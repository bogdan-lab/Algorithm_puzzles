#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr int64_t INFINITY = std::numeric_limits<int64_t>::max();

using SparseTable = std::vector<std::vector<int64_t>>;

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int64_t> BuildDataVector(int64_t size, int64_t init_value);
int64_t GetNextU(int64_t curr_val, int64_t curr_answer, int64_t idx);

int64_t GetNextV(int64_t curr_val, int64_t curr_answer, int64_t idx,
                 int64_t limit);
size_t GetLeftClosestPower2(size_t num);
SparseTable BuildMinSparseTable(const std::vector<int64_t>& data);
int64_t GetMinOnRange(const SparseTable& table, int64_t lhs, int64_t rhs);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::vector<int64_t> BuildDataVector(int64_t size, int64_t init_value) {
  std::vector<int64_t> res(size);
  res[0] = init_value;
  for (size_t i = 1; i < res.size(); ++i) {
    res[i] = (23 * res[i - 1] + 21563) % 16714589;
  }
  return res;
}

int64_t GetNextU(int64_t curr_val, int64_t curr_answer, int64_t idx,
                 int64_t limit) {
  return (17 * curr_val + 751 + curr_answer + 2 * idx) % limit + 1;
}

int64_t GetNextV(int64_t curr_val, int64_t curr_answer, int64_t idx,
                 int64_t limit) {
  return (13 * curr_val + 593 + curr_answer + 5 * idx) % limit + 1;
}

void Solution(std::istream& input) {
  int64_t n, m, a0;
  input >> n >> m >> a0;
  std::vector<int64_t> data = BuildDataVector(n, a0);
  SparseTable table = BuildMinSparseTable(data);
  int64_t u, v;
  input >> u >> v;
  int64_t answer = 0;
  int64_t prev_u = u;
  int64_t prev_v = v;
  for (int64_t i = 1; i <= m; ++i) {
    prev_u = u;
    prev_v = v;
    answer = GetMinOnRange(table, std::min(u, v) - 1, std::max(u, v) - 1);
    u = GetNextU(u, answer, i, data.size());
    v = GetNextV(v, answer, i, data.size());
  }
  std::cout << prev_u << ' ' << prev_v << ' ' << answer << '\n';
}

size_t GetLeftClosestPower2(size_t num) {
  size_t res = 0;
  while ((1 << res) <= num) {
    ++res;
  }
  return res - 1;
}

SparseTable BuildMinSparseTable(const std::vector<int64_t>& data) {
  SparseTable res(data.size());
  size_t max_pow2_num = GetLeftClosestPower2(data.size());
  for (size_t i = 0; i < data.size(); ++i) {
    res[i].resize(max_pow2_num + 1, INFINITY);
    res[i][0] = data[i];
  }

  for (size_t pow = 1; pow < res.front().size(); ++pow) {
    for (size_t start = 0; start < res.size(); ++start) {
      if (start + (1 << pow) - 1 >= res.size()) {
        break;
      }
      res[start][pow] =
          std::min(res[start][pow - 1], res[start + (1 << (pow - 1))][pow - 1]);
    }
  }
  return res;
}

int64_t GetMinOnRange(const SparseTable& table, int64_t lhs, int64_t rhs) {
  size_t pow = GetLeftClosestPower2(rhs - lhs + 1);
  return std::min(table[lhs][pow], table[rhs - (1 << pow) + 1][pow]);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(10 8 12345
3 9
)";
    Solution(ss);
    std::cout << "expected = 5 3 1565158\n";
  }
}
