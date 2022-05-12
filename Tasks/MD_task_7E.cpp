#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr int64_t kEmptyValue = std::numeric_limits<int64_t>::min();

struct Request {
  int start = 0;
  int end = 0;  // not included
  int64_t res = 0;
};

struct Node {
  int64_t val = kEmptyValue;
  int start = 0;
  int end = 0;  // not included
};

std::vector<Node> BuildEmptyTree(int n);
void ApplyRequest(std::vector<Node>& tree, int pos, int i_s, int i_e,
                  int64_t res);
void PrintArray(const std::vector<Node>& tree, int array_size);

void RecursivelyPush(std::vector<Node>& tree, int pos);

void PushCurrentvalue(std::vector<Node>& tree, int pos);

bool CheckRequests(const std::vector<Node>& tree,
                   const std::vector<Request>& data);

int Left(int index);
int Right(int index);
int Parent(int index);
bool IsLeaf(int index, int tree_size);

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;
  std::vector<Request> data;
  data.reserve(m);
  while (m--) {
    int i, j, q;
    input >> i >> j >> q;
    data.push_back({.start = i - 1, .end = j, .res = q});
  }

  std::sort(
      data.begin(), data.end(),
      [](const Request& lhs, const Request& rhs) { return lhs.res < rhs.res; });

  std::vector<Node> tree = BuildEmptyTree(n);
  tree[0].val = data.front().res;
  for (const auto& el : data) {
    ApplyRequest(tree, 0, el.start, el.end, el.res);
  }
  if (!CheckRequests(tree, data)) {
    std::cout << "inconsistent\n";
    return;
  }
  std::cout << "consistent\n";
  RecursivelyPush(tree, 0);
  PrintArray(tree, n);
  std::cout << '\n';
}

std::vector<Node> BuildEmptyTree(int n) {
  int size = 1;
  while (size < n) {
    size *= 2;
  }
  std::vector<Node> result(2 * size - 1);
  for (size_t i = size - 1, j = 0; i < result.size(); ++i, ++j) {
    result[i].start = j;
    result[i].end = j + 1;
  }
  for (int i = size - 2; i >= 0; --i) {
    result[i].start = result[Left(i)].start;
    result[i].end = result[Right(i)].end;
  }
  return result;
}

int Left(int index) { return 2 * index + 1; }
int Right(int index) { return 2 * (index + 1); }
int Parent(int index) { return (index - 1) / 2; }
bool IsLeaf(const std::vector<Node>& tree, int index) {
  return tree.size() < Left(index);
}

void ApplyRequest(std::vector<Node>& tree, int pos, int i_s, int i_e,
                  int64_t req_res) {
  if (tree[pos].start == i_s && tree[pos].end == i_e) {
    // Request exactly corresponds to the range of current node
    tree[pos].val = req_res;
    while (pos > 0) {
      pos = Parent(pos);
      tree[pos].val = std::min(tree[Left(pos)].val, tree[Right(pos)].val);
    }
    return;
  } else if (i_s >= tree[pos].end || i_e <= tree[pos].start) {
    return;
  } else {
    // Have crossection
    int li = Left(pos);
    int ri = Right(pos);
    PushCurrentvalue(tree, pos);
    ApplyRequest(tree, li, i_s, std::min(tree[li].end, i_e), req_res);
    ApplyRequest(tree, ri, std::max(i_s, tree[ri].start), i_e, req_res);
    return;
  }
}

int64_t GetMin(const std::vector<Node>& tree, int pos, int start, int end) {
  if (start >= end) return std::numeric_limits<int64_t>::max();
  if (tree[pos].start == start && tree[pos].end == end) {
    return tree[pos].val;
  } else if (start >= tree[pos].end || end <= tree[pos].start) {
    return std::numeric_limits<int64_t>::max();
  } else {
    int li = Left(pos);
    int ri = Right(pos);
    return std::min(GetMin(tree, li, start, std::min(tree[li].end, end)),
                    GetMin(tree, ri, std::max(start, tree[ri].start), end));
  }
}

bool CheckRequests(const std::vector<Node>& tree,
                   const std::vector<Request>& data) {
  for (const auto& req : data) {
    if (GetMin(tree, 0, req.start, req.end) != req.res) {
      return false;
    }
  }
  return true;
}

void PushCurrentvalue(std::vector<Node>& tree, int pos) {
  int li = Left(pos);
  if (li >= tree.size()) return;
  int ri = Right(pos);
  tree[li].val = std::max(tree[pos].val, tree[li].val);
  tree[ri].val = std::max(tree[pos].val, tree[ri].val);
}

void RecursivelyPush(std::vector<Node>& tree, int pos) {
  PushCurrentvalue(tree, pos);
  int li = Left(pos);
  if (li < tree.size()) {
    RecursivelyPush(tree, li);
    int ri = Right(pos);
    RecursivelyPush(tree, ri);
  }
}

void PrintArray(const std::vector<Node>& tree, int array_size) {
  int size = 1;
  while (size < array_size) {
    size *= 2;
  }
  int index = size - 1;
  while (array_size--) {
    std::cout << tree[index++].val << ' ';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 2
1 2 1
2 3 2
)";
    Solution(ss);
    std::cout << "expected = consistent; 1 2 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 3
1 2 1
1 1 2
2 3 2
)";
    Solution(ss);
    std::cout << "expected = inconsistent\n";
  }
  {
    std::stringstream ss;
    ss << R"(1 1
1 1 1
)";
    Solution(ss);
    std::cout << "expected = consistent; 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 3
1 1 1
2 2 2
3 3 3
)";
    Solution(ss);
    std::cout << "expected = consistent; 1 2 3 X\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 5
1 1 1
2 2 2
3 3 3
1 3 1
2 4 2
)";
    Solution(ss);
    std::cout << "expected = consistent; 1 2 3 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 9
1 1 1
2 2 2
3 3 3
1 3 1
2 4 2
4 4 4
2 3 2
3 4 3
1 4 1
)";
    Solution(ss);
    std::cout << "expected = consistent; 1 2 3 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 10
1 1 1
2 2 2
3 3 3
1 3 1
2 4 2
4 4 4
2 3 2
3 4 3
1 4 1
2 4 1
)";
    Solution(ss);
    std::cout << "expected = inconsistent\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 4
1 1 1
2 2 2
3 3 3
4 4 4
)";
    Solution(ss);
    std::cout << "expected = consistent; 1 2 3 4\n";
  }
}
