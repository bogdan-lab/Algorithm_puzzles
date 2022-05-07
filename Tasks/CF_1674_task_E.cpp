#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int SolveSeparate(const std::vector<int>& data);
int SolveByOne(const std::vector<int>& data);
int SolveNeighbours(const std::vector<int>& data);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }
  std::cout << std::min({SolveSeparate(data), SolveByOne(data),
                         SolveNeighbours(data)})
            << '\n';
}

int SolveSeparate(const std::vector<int>& data) {
  // Do not care about separation, since method is expensive -> if we have two
  // minimums closer one to another correct answer will occur in some of the
  // other methods
  std::vector<int> res(2, std::numeric_limits<int>::max());
  for (size_t i = 0; i < data.size(); ++i) {
    if (res[0] > data[i]) {
      res[0] = data[i];
    }
    if (res[0] < res[1]) {
      std::swap(res[0], res[1]);
    }
  }
  return (res[0] + 1) / 2 + (res[1] + 1) / 2;
}

int SolveByOne(const std::vector<int>& data) {
  int min_count = std::numeric_limits<int>::max();
  for (size_t i = 1; i <= data.size() - 2; ++i) {
    min_count = std::min(min_count, (data[i - 1] + data[i + 1] + 1) / 2);
  }
  return min_count;
}

int SolveNeighbours(const std::vector<int>& data) {
  int min_count = std::numeric_limits<int>::max();
  for (size_t i = 1; i < data.size(); ++i) {
    int lo = data[i - 1];
    int hi = data[i];
    if (hi < lo) std::swap(hi, lo);
    int count_to_eq = 0;
    if (hi != lo) {
      // accumulate count_to_eq and make them eq
      count_to_eq = hi - lo;
      if (lo - count_to_eq <= 0) {
        min_count = std::min(min_count, (hi + 1) / 2);
        continue;
      }
      lo -= count_to_eq;
    }
    int tripple = (lo / 3);
    lo -= tripple * 3;
    int additional = lo == 2 ? 2 : (lo == 1) ? 1 : 0;
    min_count = std::min(min_count, additional + 2 * tripple + count_to_eq);
  }
  return min_count;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
20 10 30 10 20
)";
    Solution(ss);
    std::cout << "expected = 10\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
1 8 1
)";
    Solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
7 6 6 8 5 8
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
14 3 8 10 15 4
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
1 100 100 1
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
40 10 10
)";
    Solution(ss);
    std::cout << "expected = 7\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
3 89 1
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
}
