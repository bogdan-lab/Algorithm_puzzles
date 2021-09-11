#include <iostream>
#include <sstream>
#include <vector>

struct Inverses {
  std::vector<int> sorted;
  uint64_t count = 0;

  Inverses(int val) : sorted(1) { sorted[0] = val; }
  Inverses(const Inverses& lhs, const Inverses& rhs)
      : sorted(lhs.sorted.size() + rhs.sorted.size()),
        count(lhs.count + rhs.count) {}
};

void solution(std::istream& input = std::cin);
void run_tests();
Inverses count_inverse(const std::vector<int>& data, size_t begin, size_t end);
Inverses merge_and_count(const Inverses& lhs, const Inverses& rhs);

bool left_smaller(size_t l_idx, const std::vector<int>& lhs, size_t r_idx,
                  const std::vector<int>& rhs);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

bool left_smaller(size_t l_idx, const std::vector<int>& lhs, size_t r_idx,
                  const std::vector<int>& rhs) {
  if (l_idx >= lhs.size()) return false;
  if (r_idx >= rhs.size()) return true;
  return lhs[l_idx] <= rhs[r_idx];
}

Inverses merge_and_count(const Inverses& lhs, const Inverses& rhs) {
  Inverses res(lhs, rhs);
  size_t l_idx = 0;
  size_t r_idx = 0;
  for (auto& el : res.sorted) {
    if (left_smaller(l_idx, lhs.sorted, r_idx, rhs.sorted)) {
      el = lhs.sorted[l_idx++];
    } else {
      el = rhs.sorted[r_idx++];
      if (l_idx < lhs.sorted.size()) {
        res.count += lhs.sorted.size() - l_idx;
      }
    }
  }
  return res;
}

Inverses count_inverse(const std::vector<int>& data, size_t begin, size_t end) {
  if (end - begin == 1) return {data[begin]};
  const size_t mid = (begin + end) / 2;
  return merge_and_count(count_inverse(data, begin, mid),
                         count_inverse(data, mid, end));
}

void solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::cout << count_inverse(data, 0, data.size()).count << '\n';
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(4
1 2 4 5
)";
    solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
5 4 2 1
)";
    solution(ss);
    std::cout << "expected = 6\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
1 2 5 3 4
)";
    solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(7
7 2 5 3 4 12 11
)";
    solution(ss);
    std::cout << "expected = 7\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
7 2 3 3 4
)";
    solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
1 1 1 1 1
)";
    solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(1
100
)";
    solution(ss);
    std::cout << "expected = 0\n";
  }
}
