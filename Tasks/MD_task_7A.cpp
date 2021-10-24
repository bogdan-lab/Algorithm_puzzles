#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

constexpr int64_t TASK_CONSTANT_A = (1ll << 16);
constexpr int64_t TASK_CONSTANT_B = (1ll << 30);

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int64_t> BuildInputVector(int64_t size, int64_t mult, int64_t add,
                                      int64_t init_value, int64_t limit);

std::vector<int64_t> BuildPrefixSum(const std::vector<int64_t>& data);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::vector<int64_t> BuildInputVector(int64_t size, int64_t mult, int64_t add,
                                      int64_t init_value, int64_t limit) {
  std::vector<int64_t> res(size);
  res[0] = init_value;
  for (size_t i = 1; i < res.size(); ++i) {
    res[i] = (mult * res[i - 1] + add) % limit;
  }
  return res;
}

void Solution(std::istream& input) {
  int64_t n, x, y, a0;
  input >> n >> x >> y >> a0;
  std::vector<int64_t> data = BuildInputVector(n, x, y, a0, TASK_CONSTANT_A);
  int64_t m, z, t, b0;
  input >> m >> z >> t >> b0;
  std::vector<int64_t> req_vec =
      BuildInputVector(2 * m, z, t, b0, TASK_CONSTANT_B);
  std::transform(req_vec.begin(), req_vec.end(), req_vec.begin(),
                 [&data](int64_t val) { return val % data.size(); });
  std::vector<int64_t> prefix_sum = BuildPrefixSum(data);
  int64_t total = 0;
  size_t idx = 0;
  while (2 * idx + 1 < req_vec.size()) {
    int64_t lhs = std::min(req_vec[2 * idx], req_vec[2 * idx + 1]);
    int64_t rhs = std::max(req_vec[2 * idx], req_vec[2 * idx + 1]);
    total += prefix_sum[rhs] - (lhs == 0 ? 0 : prefix_sum[lhs - 1]);
    ++idx;
  }
  std::cout << total << '\n';
}

std::vector<int64_t> BuildPrefixSum(const std::vector<int64_t>& data) {
  std::vector<int64_t> res(data.size());
  res[0] = data[0];
  for (size_t i = 1; i < data.size(); ++i) {
    res[i] += res[i - 1] + data[i];
  }
  return res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 1 2 3
3 1 -1 4
)";
    Solution(ss);
    std::cout << "expected = 23\n";
  }
}
