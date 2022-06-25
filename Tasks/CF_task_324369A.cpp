#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void ConvertToDiffArray(std::vector<int64_t>& data);
void PerformAddition(std::vector<int64_t>& diff_vec, size_t begin, size_t end,
                     int64_t val);
void ConvertToArray(std::vector<int64_t>& diff_vec);

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int64_t n;
  input >> n;
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }
  ConvertToDiffArray(data);
  int64_t q;
  input >> q;
  while (q--) {
    size_t begin, end;
    int64_t val;
    input >> begin >> end >> val;
    --begin;
    PerformAddition(data, begin, end, val);
  }
  ConvertToArray(data);
  for (const auto& el : data) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void ConvertToDiffArray(std::vector<int64_t>& data) {
  for (size_t i = data.size() - 1; i > 0; --i) {
    data[i] -= data[i - 1];
  }
}

void PerformAddition(std::vector<int64_t>& diff_vec, size_t begin, size_t end,
                     int64_t val) {
  diff_vec[begin] += val;
  if (end < diff_vec.size()) diff_vec[end] -= val;
}

void ConvertToArray(std::vector<int64_t>& diff_vec) {
  for (size_t i = 1; i < diff_vec.size(); ++i) {
    diff_vec[i] += diff_vec[i - 1];
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(1
100
3
1 1 10
1 1 -3
1 1 20
)";
    Solution(ss);
    std::cout << "expected = 127\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
0 0
5
1 1 100
1 2 -100
2 2 10
1 1 20
1 2 -30
)";
    Solution(ss);
    std::cout << "expected = -10 -120\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
1 2 3 4 -5
3
5 5 10
1 5 4
2 3 -1
)";
    Solution(ss);
    std::cout << "expected = 5 5 6 8 9\n";
  }
}
