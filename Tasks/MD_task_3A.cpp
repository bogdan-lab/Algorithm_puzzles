#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();
int get_closest(const std::vector<int>& data, int val);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int n;
  int m;
  input >> n >> m;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }
  while (m--) {
    int val;
    input >> val;
    std::cout << get_closest(data, val) << '\n';
  }
}

int get_closest(const std::vector<int>& data, int val) {
  size_t begin = 0;
  size_t end = data.size();
  while (end - begin > 1) {
    size_t mid = (begin + end) / 2;
    if (data[mid] > val) {
      end = mid;
    } else {
      begin = mid;
    }
  }
  if (data[begin] == val || end == data.size()) return data[begin];
  return val - data[begin] > data[end] - val ? data[end] : data[begin];
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(5 7
1 3 5 7 9
2 4 8 1 6 20 -7
)";
    solution(ss);
    std::cout << "expected = 1 3 7 1 5 9 1\n";
  }
}
