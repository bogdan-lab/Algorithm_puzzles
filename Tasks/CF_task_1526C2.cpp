#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr int kEmptyDrop = std::numeric_limits<int>::max();
constexpr int64_t kEmptyValue = std::numeric_limits<int64_t>::max();

struct Node {
  int max_drop = kEmptyDrop;
  size_t max_drop_id = std::numeric_limits<size_t>::max();
  int64_t health_sum = kEmptyValue;
  size_t begin = std::numeric_limits<size_t>::max();
  // end is not included in the range
  size_t end = std::numeric_limits<size_t>::min();
};

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<Node> BuildSegmentTree(const std::vector<int>& data);
size_t GetBotLevelSize(size_t data_size);

size_t Left(size_t curr_idx);
size_t Right(size_t curr_idx);
size_t Parent(size_t curr_idx);

int64_t SummarizeHealth(int64_t lhs, int64_t rhs);
Node GetRangeNode(const std::vector<Node>& seg_tree, size_t head, size_t begin,
                  size_t end);
Node AddNodes(const Node& lhs, const Node& rhs);

void DeleteElement(std::vector<Node>& seg_tree, size_t id);

bool IsIndexInside(size_t index, size_t begin, size_t end);

size_t CountPotions(const std::vector<Node>& seg_tree);

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
  std::vector<Node> seg_tree = BuildSegmentTree(data);
  for (size_t end = 1; end < n + 1; ++end) {
    Node curr_node = GetRangeNode(seg_tree, 0, 0, end);
    while (curr_node.health_sum < 0) {
      DeleteElement(seg_tree, curr_node.max_drop_id);
      curr_node = GetRangeNode(seg_tree, 0, 0, end);
    }
  }
  std::cout << CountPotions(seg_tree) << '\n';
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
    result[j].max_drop_id = j;
    result[j].begin = i;
    result[j].end = i + 1;
  }
  for (size_t i = result.size() - 1; i > 0; i -= 2) {
    result[Parent(i)] = AddNodes(result[i], result[i - 1]);
  }
  return result;
}

Node AddNodes(const Node& lhs, const Node& rhs) {
  Node result;
  result.health_sum = SummarizeHealth(lhs.health_sum, rhs.health_sum);
  if (lhs.max_drop < rhs.max_drop) {
    result.max_drop = lhs.max_drop;
    result.max_drop_id = lhs.max_drop_id;
  } else if (lhs.max_drop > rhs.max_drop) {
    result.max_drop = rhs.max_drop;
    result.max_drop_id = rhs.max_drop_id;
  } else {
    result.max_drop = rhs.max_drop;
    result.max_drop_id = std::min(rhs.max_drop_id, lhs.max_drop_id);
  }
  result.begin = std::min(lhs.begin, rhs.begin);
  result.end = std::max(lhs.end, rhs.end);
  return result;
}

bool IsRangeInside(size_t rng_begin, size_t rng_end, size_t begin, size_t end) {
  return begin <= rng_begin && rng_end <= end;
}

Node GetRangeNode(const std::vector<Node>& seg_tree, size_t head, size_t begin,
                  size_t end) {
  if (seg_tree[head].begin >= end || seg_tree[head].end <= begin) {
    return {};
  }
  if (seg_tree[head].begin == begin && seg_tree[head].end == end) {
    return seg_tree[head];
  }
  size_t li = Left(head);
  if (IsRangeInside(begin, end, seg_tree[li].begin, seg_tree[li].end)) {
    return GetRangeNode(seg_tree, li, begin, end);
  }
  size_t ri = Right(head);
  if (IsRangeInside(begin, end, seg_tree[ri].begin, seg_tree[ri].end)) {
    return GetRangeNode(seg_tree, ri, begin, end);
  }
  // Here we have crossection and do not entirely fit in any subtree
  return AddNodes(GetRangeNode(seg_tree, li, begin, seg_tree[li].end),
                  GetRangeNode(seg_tree, ri, seg_tree[ri].begin, end));
}

void DeleteElement(std::vector<Node>& seg_tree, size_t id) {
  seg_tree[id].health_sum = kEmptyValue;
  seg_tree[id].max_drop = kEmptyDrop;
  while (id != 0) {
    id = Parent(id);
    seg_tree[id] = AddNodes(seg_tree[Left(id)], seg_tree[Right(id)]);
  }
}

size_t CountPotions(const std::vector<Node>& seg_tree) {
  size_t count = 0;
  for (size_t i = (seg_tree.size() + 1) / 2 - 1; i < seg_tree.size(); ++i) {
    if (seg_tree[i].health_sum != kEmptyValue) {
      count++;
    }
  }
  return count;
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
  {
    std::stringstream ss;
    ss << R"(12
-3 -3 -7 -7 -1 -7 3 3 -2 -1 0 -7
)";
    Solution(ss);
    std::cout << "expected = 5\n";
  }
}
