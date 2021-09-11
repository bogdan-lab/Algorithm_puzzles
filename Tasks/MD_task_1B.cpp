#include <iostream>
#include <sstream>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();
std::vector<int> merge_sort(const std::vector<int>& data, size_t begin,
                            size_t end);
std::vector<int> merge(const std::vector<int>& lhs,
                       const std::vector<int>& rhs);
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
  return lhs[l_idx] < rhs[r_idx];
}

std::vector<int> merge(const std::vector<int>& lhs,
                       const std::vector<int>& rhs) {
  std::vector<int> res(lhs.size() + rhs.size());
  size_t l_idx = 0;
  size_t r_idx = 0;
  for (auto& el : res) {
    if (left_smaller(l_idx, lhs, r_idx, rhs)) {
      el = lhs[l_idx++];
    } else {
      el = rhs[r_idx++];
    }
  }
  return res;
}

std::vector<int> merge_sort(const std::vector<int>& data, size_t begin,
                            size_t end) {
  if (end - begin == 1) return {data[begin]};
  size_t mid = (begin + end) / 2;
  return merge(merge_sort(data, begin, mid), merge_sort(data, mid, end));
}

void solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<int> res = merge_sort(data, 0, data.size());

  for (const auto& el : res) {
    std::cout << el << ' ';
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(10
1 8 2 1 4 7 3 2 3 6
)";
    solution(ss);
  }
}
