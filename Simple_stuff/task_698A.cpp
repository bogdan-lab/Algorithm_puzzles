#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#define EMPTY 4

size_t get_opposite(size_t state) {
  switch (state) {
    case 0:
      return EMPTY;
    case 1:
      return 2;
    case 2:
      return 1;
    case 3:
      return EMPTY;
    default:
      return EMPTY;
  }
}

size_t count_free_days(const std::vector<size_t>& vec) {
  size_t count = 0;
  size_t prev_state = EMPTY;
  for (auto el : vec) {
    if (el == prev_state || el == 0) {
      ++count;
      prev_state = EMPTY;
    } else if (el == 3) {
      prev_state = get_opposite(prev_state);
    } else {
      prev_state = el;
    }
  }
  return count;
}

void solution(std::istream& input = std::cin) {
  size_t n;
  input >> n;
  std::vector<size_t> vec;
  vec.reserve(n);
  std::copy_n(std::istream_iterator<size_t>(input), n, std::back_inserter(vec));
  std::cout << count_free_days(vec) << '\n';
}

void do_tests() {
  {
    std::stringstream ss;
    ss << R"(4
    1 3 2 0
    )";
    solution(ss);
  }
  {
    std::stringstream ss;
    ss << R"(7
    1 3 3 2 1 2 3
    )";
    solution(ss);
  }
  {
    std::stringstream ss;
    ss << R"(2
        2 2
        )";
    solution(ss);
  }
}

int main() {
  // do_tests();
  solution(std::cin);
  return 0;
}
