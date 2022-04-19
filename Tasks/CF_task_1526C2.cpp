#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr int kEmptyDrop = std::numeric_limits<int>::max();
constexpr int64_t kEmptyValue = std::numeric_limits<int64_t>::max();

struct Node {
  int max_drop = kEmptyDrop;
  int64_t health_sum = kEmptyValue;
};

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<Node> BuildSegmentTree(const std::vector<int>& data);
size_t GetBotLevelSize(size_t data_size);

size_t Left(size_t curr_idx);
size_t Right(size_t curr_idx);
size_t Parent(size_t curr_idx);

int64_t SummarizeHealth(int64_t lhs, int64_t rhs);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }
  std::vector<Node> seg_tree = BuildSegmentTree(data);
  // TODO iterate over indexes and check if health_cum for the seg_tree is
  // lower_than 0
  // If it is, than throw away max_drop elements from the subtree
  // until it becomes positive
  // move further
  std::cout << "To be continued....\n";
}

size_t GetBotLevelSize(size_t data_size) {
  size_t result = 2;
  while (result < data_size) {
    result *= 2;
  }
  return result;
}

std::vector<Node> BuildSegmentTree(const std::vector<int>& data) {
  size_t bot_size = GetBotLevelSize(data.size());
  std::vector<Node> result(2 * bot_size - 1);
  for (size_t i = 0, j = bot_size - 1; i < data.size(); ++i, ++j) {
    result[j].health_sum = data[i];
    result[j].max_drop = data[i];
  }
  for (size_t i = result.size() - 1; i > 0; i -= 2) {
    size_t p_i = Parent(i);
    result[p_i].health_sum =
        SummarizeHealth(result[i].health_sum, result[i - 1].health_sum);
    result[p_i].max_drop = std::min(result[i].max_drop, result[i - 1].max_drop);
  }
  return result;
}

int64_t SummarizeHealth(int64_t lhs, int64_t rhs) {
  if (lhs == kEmptyValue) return rhs;
  if (rhs == kEmptyValue) return lhs;
  return lhs + rhs;
}

size_t Left(size_t curr_idx) { return 2 * curr_idx + 1; }

size_t Right(size_t curr_idx) { return 2 * curr_idx + 2; }
size_t Parent(size_t curr_idx) { return (curr_idx + 1) / 2 - 1; }

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
4 -4 1 -3 1 -3
)";
    Solution(ss);
    std::cout << "expected = 5\n";
  }
}
