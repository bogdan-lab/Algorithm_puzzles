#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();
int count_numbers(const std::vector<int>& data, int left_val, int right_val);
size_t lower_bound(const std::vector<int>& data, int val);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }
  std::sort(data.begin(), data.end());
  int m;
  input >> m;
  while (m--) {
    int left;
    int right;
    input >> left >> right;
    std::cout << count_numbers(data, left, right) << '\n';
  }
}

int count_numbers(const std::vector<int>& data, int left_val, int right_val) {
  return lower_bound(data, right_val + 1) - lower_bound(data, left_val);
}

size_t lower_bound(const std::vector<int>& data, int val) {
  size_t begin = 0;
  size_t end = data.size();
  while (end - begin > 1) {
    size_t mid = (end + begin) / 2;
    if (data[mid] >= val) {
      end = mid;
    } else {
      begin = mid;
    }
  }
  return data[begin] >= val ? begin : end;
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(7
10 1 10 3 4 1 1
4
1 10
2 9
3 4
2 2
)";
    solution(ss);
    std::cout << "expected = 7 2 2 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(7
1 1 1 1 1 1 1
4
1 10
-6 9
3 4
1 1
)";
    solution(ss);
    std::cout << "expected = 7 7 0 7\n";
  }
}
