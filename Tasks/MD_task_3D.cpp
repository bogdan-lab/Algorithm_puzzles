#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();
int calc_optimaL_length(const std::vector<int>& data, int required_num);
bool check_if_can_make(int ropes_num, int length, const std::vector<int>& data);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int rope_num;
  int required_num;
  input >> rope_num >> required_num;
  std::vector<int> data(rope_num);
  for (auto& el : data) {
    input >> el;
  }
  std::cout << calc_optimaL_length(data, required_num) << '\n';
}

int calc_optimaL_length(const std::vector<int>& data, int required_num) {
  int len_left = 0;
  int len_right = *std::max_element(data.begin(), data.end()) + 1;
  while (len_right - len_left > 1) {
    int len_mid = (len_left + len_right) / 2;
    if (check_if_can_make(required_num, len_mid, data)) {
      len_left = len_mid;
    } else {
      len_right = len_mid;
    }
  }
  return len_left;
}

bool check_if_can_make(int ropes_num, int length,
                       const std::vector<int>& data) {
  int count = 0;
  for (const auto& el : data) {
    count += el / length;
  }
  return count >= ropes_num;
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(4 11
802
743
457
539
)";
    solution(ss);
    std::cout << "expected = 200\n";
  }
  {
    std::stringstream ss;
    ss << R"(1 11
10
)";
    solution(ss);
    std::cout << "expected = 0\n";
  }
}
