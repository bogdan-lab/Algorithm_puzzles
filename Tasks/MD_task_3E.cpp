#include <algorithm>
#include <iostream>
#include <sstream>

void solution(std::istream& input = std::cin);
void run_tests();
bool can_copy_in(int full_time, int lhs_time, int rhs_time, int copy_num);
int calc_min_copy_time(int copy_num, int lhs_time, int rhs_time);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int lhs_time;
  int rhs_time;
  int copy_num;
  input >> copy_num >> lhs_time >> rhs_time;
  std::cout << calc_min_copy_time(copy_num, lhs_time, rhs_time) << '\n';
}

int calc_min_copy_time(int copy_num, int lhs_time, int rhs_time) {
  int begin = 0;
  int end = copy_num * std::min(lhs_time, rhs_time);
  while (end - begin > 1) {
    int mid = (begin + end) / 2;
    if (can_copy_in(mid, lhs_time, rhs_time, copy_num)) {
      end = mid;
    } else {
      begin = mid;
    }
  }
  return end;
}

bool can_copy_in(int full_time, int lhs_time, int rhs_time, int copy_num) {
  full_time -= std::min(lhs_time, rhs_time);
  int count = 1 + full_time / lhs_time + full_time / rhs_time;
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
