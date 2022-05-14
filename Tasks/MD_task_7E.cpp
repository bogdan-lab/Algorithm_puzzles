#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <tuple>
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

void ApplyRequest(std::vector<Node>& tree, int pos, Request rec);
int64_t GetMin(const std::vector<Node>& tree, int pos, int start, int end);
void PrintArray(const std::vector<Node>& tree, int arr_size);
int64_t GetNonEmptyAncestor(const std::vector<Node>& tree, int pos);

int Left(int index) { return 2 * index + 1; }
int Right(int index) { return 2 * (index + 1); }
int Parent(int index) { return (index - 1) / 2; }

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

  std::sort(data.begin(), data.end(), [](const auto& lhs, const auto& rhs) {
    int ls = lhs.end - lhs.start;
    int rs = rhs.end - rhs.start;
    return std::tie(lhs.res, ls) > std::tie(rhs.res, rs);
  });

  std::vector<Node> tree = BuildEmptyTree(n);
  for (const auto& rec : data) {
    int64_t curr_val = GetMin(tree, 0, rec.start, rec.end);
    if (curr_val != rec.res) {
      ApplyRequest(tree, 0, rec);
    }
  }

  for (const auto& rec : data) {
    if (GetMin(tree, 0, rec.start, rec.end) != rec.res) {
      std::cout << "inconsistent\n";
      return;
    }
  }
  std::cout << "consistent\n";
  PrintArray(tree, n);
}

void PrintArray(const std::vector<Node>& tree, int arr_size) {
  int pos = 1;
  while (pos < arr_size) {
    pos *= 2;
  }
  --pos;
  while (arr_size--) {
    int64_t v = tree[pos].val;
    if (v == kEmptyValue) {
      v = GetNonEmptyAncestor(tree, pos);
    }
    std::cout << v << ' ';
    ++pos;
  }
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

void BalanceCurrent(std::vector<Node>& tree, int pos) {
  int pi = Parent(pos);
  int li = Left(pi);
  int ri = Right(pi);
  if (tree[li].val == kEmptyValue) {
    tree[li].val = tree[pi].val;
  }
  if (tree[ri].val == kEmptyValue) {
    tree[ri].val = tree[pi].val;
  }
}

void EnsureInvariant(std::vector<Node>& tree, int pos) {
  if (pos != 0) {
    int pi = Parent(pos);
    BalanceCurrent(tree, pos);
    while (pi >= 0) {
      tree[pi].val = std::min(tree[Left(pi)].val, tree[Right(pi)].val);
      if (pi == 0) break;
      pi = Parent(pi);
    }
  }
}

void ApplyRequest(std::vector<Node>& tree, int pos, Request rec) {
  if (rec.start >= rec.end || pos >= tree.size()) return;
  if (rec.start == tree[pos].start && rec.end == tree[pos].end) {
    int li = Left(pos);
    int ri = Right(pos);
    if (tree[pos].val == kEmptyValue) {
      tree[pos].val = rec.res;
      EnsureInvariant(tree, pos);
      return;
    } else if (li < tree.size() && tree[li].val == kEmptyValue &&
               tree[ri].val == kEmptyValue) {
      tree[pos].val = rec.res;
      EnsureInvariant(tree, pos);
      return;
    } else if (li < tree.size() && tree[li].val == kEmptyValue &&
               tree[ri].val != kEmptyValue) {
      // Here rely on fact that requests with small result comes later
      tree[pos].val = rec.res;
      tree[li].val = rec.res;
      EnsureInvariant(tree, li);
      return;
    } else if (ri < tree.size() && tree[ri].val == kEmptyValue) {
      tree[pos].val = rec.res;
      tree[ri].val = rec.res;
      EnsureInvariant(tree, ri);
      return;
    }
    // Here we are in the node and everything is filled -> find recursively what
    // can be replaced
  }
  Request lhs = rec;
  int li = Left(pos);
  lhs.end = std::min(tree[li].end, rec.end);
  ApplyRequest(tree, li, lhs);
  Request rhs = rec;
  int ri = Right(pos);
  rhs.start = std::max(tree[ri].start, rec.start);
  ApplyRequest(tree, ri, rhs);
}

int64_t GetMin(const std::vector<Node>& tree, int pos, int start, int end) {
  if (start >= end || pos >= tree.size()) return kEmptyValue;
  if (tree[pos].start == start && tree[pos].end == end) {
    return tree[pos].val;
  }
  int li = Left(pos);
  int ri = Right(pos);
  return std::min(GetMin(tree, li, start, std::min(tree[li].end, end)),
                  GetMin(tree, ri, std::max(start, tree[ri].start), end));
}

int64_t GetNonEmptyAncestor(const std::vector<Node>& tree, int pos) {
  while (pos > 0) {
    pos = Parent(pos);
    if (tree[pos].val != kEmptyValue) {
      return tree[pos].val;
    }
  }
  return tree[pos].val;
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
    std::cout << "==============================\n";
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
    std::cout << "==============================\n";
  }
  {
    std::stringstream ss;
    ss << R"(1 1
1 1 1
)";
    Solution(ss);
    std::cout << "expected = consistent; 1\n";
    std::cout << "==============================\n";
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
    std::cout << "==============================\n";
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
    std::cout << "expected = consistent; 1 2 3 >2\n";
    std::cout << "==============================\n";
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
    std::cout << "==============================\n";
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
    std::cout << "==============================\n";
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
    std::cout << "==============================\n";
  }
  {
    std::stringstream ss;
    ss << R"(1 2
1 1 1
1 1 4
)";
    Solution(ss);
    std::cout << "expected = inconsistent\n";
    std::cout << "==============================\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 4
1 1 1
2 2 1
3 3 1
4 4 1
)";
    Solution(ss);
    std::cout << "expected = consistent; 1 1 1 1\n";
    std::cout << "==============================\n";
  }
  {
    std::stringstream ss;
    ss << R"(8 3
3 6 5
1 4 3
5 8 4
)";
    Solution(ss);
    std::cout << "expected = consistent; 3 3 5 5 5 5 4 4\n";
    std::cout << "==============================\n";
  }
  {
    std::stringstream ss;
    ss << R"(8 3
3 6 3
1 4 5
5 8 4
)";
    Solution(ss);
    std::cout << "expected = inconsistent\n";
    std::cout << "==============================\n";
  }
  {
    std::stringstream ss;
    ss << R"(8 4
3 6 5
1 4 3
5 8 4
1 2 6
)";
    Solution(ss);
    std::cout << "expected = inconsistent\n";
    std::cout << "==============================\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 4
2 3 3
1 4 1
4 4 5
2 2 6
)";
    Solution(ss);
    std::cout << "expected = consistent 1 6 3 5\n";
    std::cout << "==============================\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 4
1 4 1
2 4 2
3 4 3
4 4 4
)";
    Solution(ss);
    std::cout << "expected = consistent 1 2 3 4\n";
    std::cout << "==============================\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 4
1 4 4
2 4 3
3 4 2
4 4 1
)";
    Solution(ss);
    std::cout << "expected = inconsistent\n";
    std::cout << "==============================\n";
  }
}
