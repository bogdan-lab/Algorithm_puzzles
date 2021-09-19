#include <iostream>
#include <sstream>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();

constexpr size_t MAX_ELEMENT = 100;

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  std::vector<size_t> count(MAX_ELEMENT + 1);
  size_t val = 0;
  size_t element_num = 0;
  while (input >> val) {
    count[val]++;
    element_num++;
  }

  std::vector<size_t> sorted(element_num);
  size_t s_idx = 0;
  for (size_t i = 0; i < count.size(); ++i) {
    while (count[i]--) {
      sorted[s_idx++] = i;
    }
  }

  for (const auto& el : sorted) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(7 3 4 2 5)";
    solution(ss);
  }
}
