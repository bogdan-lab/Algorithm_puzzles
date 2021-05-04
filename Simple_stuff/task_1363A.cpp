#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

bool check_data(const std::vector<int>& data, int x) {
  int odd_cnt = 0;
  int even_cnt = 0;
  int odd_required = 1;
  int even_required = x - 1;
  for (int i = 0; i < data.size(); i++) {
    if (!(data[i] % 2)) {
      ++even_cnt;
    } else {
      ++odd_cnt;
      if (odd_cnt % 2 && odd_cnt != 1 && (odd_required + 2) <= x) {
        odd_required += 2;
        even_required -= 2;
      }
    }
    if (odd_required <= odd_cnt && even_required <= even_cnt) {
      return true;
    }
  }
  return false;
}

void solution(std::istream& input = std::cin) {
  int t;
  input >> t;
  while (t--) {
    int n, x;
    input >> n >> x;
    std::vector<int> vec;
    vec.reserve(n);
    std::copy_n(std::istream_iterator<int>(input), n, std::back_inserter(vec));
    std::cout << (check_data(vec, x) ? "YES" : "NO") << '\n';
  }
}

int main() {
  /* std::stringstream ss;
   ss << R"(4
 3 1
 16 11 12
 10 3
 13 12 9 1 9 8 4 19 16 19
 3 2
 3 2 6
 9 7
 11 14 1 6 3 12 3 20 16
 )";*/
  solution();
  return 0;
}
