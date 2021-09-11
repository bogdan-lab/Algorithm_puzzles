#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();
void mk_sort(std::vector<int>& data);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void mk_sort(std::vector<int>& data) {
  for (size_t i = 1; i < data.size(); ++i) {
    size_t j = i;
    while (j > 0 && data[j] < data[j - 1]) {
      std::swap(data[j - 1], data[j]);
      --j;
    }
  }
}

void solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  mk_sort(data);

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
