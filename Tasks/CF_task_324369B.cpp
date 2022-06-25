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
  ConvertToDiffArray(data);
  int64_t q;
  input >> q;
  while (q--) {
    size_t begin, end;
    int64_t d;
    input >> begin >> end >> d;
    --begin;
    PerformAddition(data, begin, end, d);
  }
  ConvertToArray(data);
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
  if (end < diff_vec.size()) diff_vec[end] -= (end - begin + 1) * val;
  if (end + 1 < diff_vec.size()) diff_vec[end + 1] += (end - begin) * val;
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
10
3
1 1 40
1 1 0
1 1 -15
)";
    Solution(ss);
    std::cout << "expected = 35\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
10 20
3
1 2 6
1 1 15
1 2 -1
)";
    Solution(ss);
    std::cout << "expected = 30 30\n";
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
    std::cout << "expected = 5 9 13 20 25\n";
  }
}
