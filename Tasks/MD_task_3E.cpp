#include <algorithm>
#include <iostream>
#include <sstream>

void solution(std::istream& input = std::cin);
void run_tests();
bool can_copy_in(size_t full_time, size_t lhs_time, size_t rhs_time,
                 size_t copy_num);
size_t calc_min_copy_time(size_t copy_num, size_t lhs_time, size_t rhs_time);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  size_t lhs_time;
  size_t rhs_time;
  size_t copy_num;
  input >> copy_num >> lhs_time >> rhs_time;
  std::cout << calc_min_copy_time(copy_num, lhs_time, rhs_time) << '\n';
}

size_t calc_min_copy_time(size_t copy_num, size_t lhs_time, size_t rhs_time) {
  size_t begin = 0;
  size_t end = copy_num * std::min(lhs_time, rhs_time);
  while (end - begin > 1) {
    size_t mid = (begin + end) / 2;
    if (can_copy_in(mid, lhs_time, rhs_time, copy_num)) {
      end = mid;
    } else {
      begin = mid;
    }
  }
  return end;
}

bool can_copy_in(size_t full_time, size_t lhs_time, size_t rhs_time,
                 size_t copy_num) {
  size_t first_copy_time = std::min(lhs_time, rhs_time);
  if (first_copy_time > full_time) return false;
  full_time -= first_copy_time;
  size_t count = 1 + full_time / lhs_time + full_time / rhs_time;
  return count >= copy_num;
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(4 1 1
)";
    solution(ss);
    std::cout << "expected = 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 1 2
)";
    solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(1 1 1
)";
    solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(7 1 10
)";
    solution(ss);
    std::cout << "expected = 7\n";
  }
  {
    std::stringstream ss;
    ss << R"(10 2 3
)";
    solution(ss);
    std::cout << "expected = 14\n";
  }
}
