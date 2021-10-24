#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

constexpr int64_t TASK_CONSTANT_A = (1ll << 16);
constexpr int64_t TASK_CONSTANT_B = (1ll << 30);

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int64_t n, x, y, curr_a;
  input >> n >> x >> y >> curr_a;

  auto get_next_a = [x, y](int64_t curr_value) {
    return (x * curr_value + y) % TASK_CONSTANT_A;
  };

  std::vector<int64_t> data;
  data.reserve(n);
  data.push_back(curr_a);
  for (int64_t i = 1; i < n; ++i) {
    curr_a = get_next_a(curr_a);
    data.push_back(data[i - 1] + curr_a);
  }

  int64_t m, z, t, b1;
  input >> m >> z >> t >> b1;

  auto get_next_b = [z, t](int64_t curr_value) {
    int64_t val = (z * curr_value + t) % TASK_CONSTANT_B;
    return val < 0 ? TASK_CONSTANT_B + val : val;
  };

  int64_t total = 0;
  int64_t b2 = get_next_b(b1);
  while (m--) {
    int64_t req_1 = b1 % data.size();
    int64_t req_2 = b2 % data.size();
    int64_t lhs = std::min(req_1, req_2);
    int64_t rhs = std::max(req_1, req_2);

    total += data[rhs] - (lhs == 0 ? 0 : data[lhs - 1]);
    b1 = get_next_b(b2);
    b2 = get_next_b(b1);
  }
  std::cout << total << '\n';
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
