#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr int64_t kEmptyValue = std::numeric_limits<int64_t>::max();

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
bool ApplyRequest(std::vector<Node>& tree, int pos, int i_s, int i_e,
                  int64_t res);
bool PushValue(std::vector<Node>& tree, int pos);
void PrintArray(const std::vector<Node>& tree, int array_size);

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

  std::vector<Node> tree = BuildEmptyTree(n);
  for (const auto& el : data) {
    if (!ApplyRequest(tree, 0, el.start, el.end, el.res)) {
      std::cout << "inconsistent\n";
      return;
    }
  }
  std::cout << "consistent\n";
  PrintArray(tree, n);
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

bool ApplyRequest(std::vector<Node>& tree, int pos, int i_s, int i_e,
                  int64_t req_res) {
  if (tree[pos].start == i_s && tree[pos].end == i_e) {
    // Request exactly corresponds to the range of current node
    // If it is not empty -> I recieved two different answers on the same range
    if (tree[pos].val == kEmptyValue) {
      tree[pos].val = req_res;
      return true;
    }
    return req_res == tree[pos].val;
  } else if (tree[pos].start <= i_s && tree[pos].end >= i_e) {
    // Request is totally inside the current node
    // Recursively call on the left and right parts of this node.
    // If we have empty values below we need to push current value.
  } else if (tree[pos].end > i_s && tree[pos].end <= i_e &&
             tree[pos].start < i_s) {
    // Request is on the right wing of the node.
    // Push what is needed and
    // Recursively call right wing
    // If left wing crossects with the request call it recursively
    // Otherwise store there old value.
  } else {
    // Request is on the left wing of the node.
    // Do similarly to the above
  }
}

void PrintArray(const std::vector<Node>& tree, int array_size) {
  int size = 1;
  while (size < array_size) {
    size *= 2;
  }
  int index = size - 1;
  while (array_size--) {
    int64_t res = tree[index].val;
    int ci = index;
    while (res == kEmptyValue) {
      ci = Parent(ci);
      res = tree[ci].val;
    }
    std::cout << res << ' ';
    index++;
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
