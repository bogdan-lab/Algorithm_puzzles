#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

void solution(std::istream& input = std::cin);
void run_tests();
int to_int(char ch);

size_t count_good_intervals(const std::vector<int>& full);
std::vector<int> get_integral(const std::vector<int>& full);

int main() {
  //run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::vector<int> full_interval;
    full_interval.reserve(n);
    std::string rec;
    input >> rec;
    for(size_t i=0; i<rec.size(); ++i){
      full_interval.push_back(to_int(rec[i]));
    }

    std::cout << count_good_intervals(full_interval) << '\n';
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(3
3
120
5
11011
6
600005
)";
    solution(ss);
    std::cout << "expected = 3 6 1\n";
  }
}

int to_int(char ch) { return static_cast<int>(ch) - 48; }

std::vector<int> get_integral(const std::vector<int>& full) {
  std::vector<int> res(full.size() + 1);
  for (size_t i = 1; i < res.size(); ++i) {
    res[i] = res[i - 1] + full[i - 1];
  }
  return res;
}

size_t count_good_intervals(const std::vector<int>& full) {
  std::vector<int> integral = get_integral(full);
  size_t count = 0;

  for (size_t i = 1; i < integral.size(); ++i) {
    for (size_t j = i; j < integral.size(); ++j) {
      int sub_sum = integral[j] - integral[i] + full[i-1];
      int sub_idx = j - i + 1;
      count += sub_sum == sub_idx;
    }
  }

  return count;
}
