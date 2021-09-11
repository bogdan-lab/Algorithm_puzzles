#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();
void quick_sort(std::vector<int>& data, size_t begin, size_t end,
                std::mt19937& rnd);
size_t partition(std::vector<int>& data, size_t begin, size_t end,
                 std::mt19937& rnd);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

size_t partition(std::vector<int>& data, size_t begin, size_t end,
                 std::mt19937& rnd) {
  std::uniform_int_distribution<size_t> dist(begin, end - 1);
  std::swap(data[dist(rnd)], data[end - 1]);
  size_t pivot = end - 1;
  size_t big_idx = pivot;
  size_t small_idx = begin;
  while (big_idx > small_idx) {
    while (big_idx > begin && data[big_idx - 1] >= data[pivot]) {
      --big_idx;
    }
    while (small_idx < data.size() && data[small_idx] < data[pivot]) {
      ++small_idx;
    }
    if (small_idx < big_idx) {
      std::swap(data[small_idx], data[big_idx - 1]);
    }
  }
  std::swap(data[pivot], data[big_idx]);
  return big_idx;
}

void quick_sort(std::vector<int>& data, size_t begin, size_t end,
                std::mt19937& rnd) {
  if (end - begin <= 1) return;
  size_t p_idx = partition(data, begin, end, rnd);
  quick_sort(data, begin, p_idx, rnd);
  quick_sort(data, p_idx + 1, end, rnd);
}

void solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }
  std::mt19937 rnd(42);
  quick_sort(data, 0, data.size(), rnd);

  for (const auto& el : data) {
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
