#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr size_t INVALID_IDX = std::numeric_limits<size_t>::max();

void Solution(std::istream& input = std::cin);
void RunTests();

size_t GetMaxSubsetFor(const std::vector<int>& data,
                       const std::vector<size_t>& sizes, size_t curr_idx);
std::vector<int> GetPath(const std::vector<size_t>& parents,
                         const std::vector<int>& data, size_t end_idx);

int main() {
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

  std::vector<size_t> max_len(n);
  max_len[0] = 1;
  std::vector<size_t> parents(n);
  parents[0] = INVALID_IDX;
  for (size_t i = 1; i < data.size(); ++i) {
    size_t idx = GetMaxSubsetFor(data, max_len, i);
    parents[i] = idx;
    max_len[i] = idx == INVALID_IDX ? 1 : max_len[idx] + 1;
  }

  size_t best_idx =
      std::max_element(max_len.begin(), max_len.end()) - max_len.begin();
  std::cout << max_len[best_idx] << '\n';
  std::vector<int> path = GetPath(parents, data, best_idx);
  for (const auto& el : path) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

std::vector<int> GetPath(const std::vector<size_t>& parents,
                         const std::vector<int>& data, size_t end_idx) {
  std::vector<int> result;
  while (end_idx != INVALID_IDX) {
    result.push_back(data[end_idx]);
    end_idx = parents[end_idx];
  }
  std::reverse(result.begin(), result.end());
  return result;
}

size_t GetMaxSubsetFor(const std::vector<int>& data,
                       const std::vector<size_t>& sizes, size_t curr_idx) {
  size_t max_size = 0;
  size_t max_idx = INVALID_IDX;
  for (size_t i = 0; i < curr_idx; ++i) {
    if (data[i] < data[curr_idx] && max_size < sizes[i]) {
      max_size = sizes[i];
      max_idx = i;
    }
  }
  return max_idx;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(8
1 4 1 5 3 3 4 2
)";
    Solution(ss);
    std::cout << "expected = 3; 1 4 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
1 2 3
)";
    Solution(ss);
    std::cout << "expected = 3; 1 2 3\n";
  }
}
