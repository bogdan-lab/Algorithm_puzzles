#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
int64_t ProcessRequest(int64_t lcm_ab, int64_t b, int64_t l, int64_t r);
int64_t GetLCM(int64_t a, int64_t b);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int64_t t;
  input >> t;
  while (t--) {
    int64_t a, b, q;
    input >> a >> b >> q;
    if (a > b) {
      std::swap(a, b);
    }
    int64_t lcm_ab = GetLCM(a, b);
    std::vector<int64_t> answer;
    answer.reserve(q);
    while (q--) {
      int64_t l, r;
      input >> l >> r;
      answer.push_back(ProcessRequest(lcm_ab, b, l, r));
    }
    for (const auto& el : answer) {
      std::cout << el << ' ';
    }
    std::cout << '\n';
  }
}

int64_t GetLCM(int64_t a, int64_t b) {
  int64_t init_a = a;
  int64_t init_b = b;
  while (b != 0) {
    int64_t t = b;
    b = a % b;
    a = t;
  }
  return (init_a * init_b) / a;
}

int64_t ProcessRequest(int64_t lcm_ab, int64_t b, int64_t l, int64_t r) {
  if (r == 1) return 0;
  if (r < b) return 0;
  // count how many of that occurs in the range
  int64_t all_count = r / lcm_ab;
  int64_t start_count = l / lcm_ab;
  int64_t count = all_count - start_count;
  // subtract adjusted occuring_number*b
  int64_t bad_val_count = count * b;
  int64_t last = count * lcm_ab + b;
  if (last > r) {
    bad_val_count -= b;
    bad_val_count += r - count * lcm_ab + 1;
  }
  return r - std::max(b, l) + 1 - bad_val_count;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
4 6 5
1 1
1 3
1 5
1 7
1 9
7 10 2
7 8
100 200
)";
    Solution(ss);
    std::cout << "expected = 0 0 0 2 4 || 0 91\n";
  }
}
