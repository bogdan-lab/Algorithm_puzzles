#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int64_t GetNextPower(int64_t val) {
  int64_t res = 1;
  while (res < val) {
    res *= 2;
  }
  return res;
}

int Left(int v) { return 2 * v + 1; }
int Right(int v) { return 2 * v + 2; }
int Parent(int v) { return (v - 1) / 2; }

struct Node {
  int val = 0;
  int apply = 0;
  int begin = 0;
  int end = 0;
};

bool IsLeaf(const Node& n) { return n.end == n.begin + 1; }

Node Merge(const Node& l, const Node& r) {
  Node res;
  res.begin = l.begin;
  res.end = r.end;
  return res;
}

std::vector<Node> BuildTree(const std::vector<int>& data) {
  int64_t last_lvl_size = GetNextPower(data.size());
  int64_t total_size = 2 * last_lvl_size - 1;

  std::vector<Node> tree(total_size);
  for (int i = last_lvl_size - 1, j = 0; i < tree.size(); ++i, ++j) {
    if (j < data.size()) {
      tree[i].val = data[j];
    }
    tree[i].begin = j;
    tree[i].end = j + 1;
  }

  for (int i = last_lvl_size - 2; i >= 0; --i) {
    tree[i] = Merge(tree[Left(i)], tree[Right(i)]);
  }

  return tree;
}

int CalcSum(int val) {
  int sum = 0;
  while (val) {
    sum += val % 10;
    val /= 10;
  }
  return sum;
}

void Push(std::vector<Node>& tree, int ci) {
  if (!tree[ci].apply) return;
  if (IsLeaf(tree[ci])) {
    while (tree[ci].apply) {
      tree[ci].val = CalcSum(tree[ci].val);
      --tree[ci].apply;
    }
  } else {
    int li = Left(ci);
    int ri = Right(ci);
    tree[li].apply += tree[ci].apply;
    tree[ri].apply += tree[ci].apply;
    tree[ci].apply = 0;
  }
}

void Apply(std::vector<Node>& tree, int ci, int begin, int end) {
  if (end <= begin) return;
  if (end <= tree[ci].begin || begin >= tree[ci].end) return;
  Push(tree, ci);
  if (tree[ci].begin == begin && tree[ci].end == end) {
    ++tree[ci].apply;
    return;
  }

  int li = Left(ci);
  int ri = Right(ci);
  if (li < tree.size()) {
    Apply(tree, li, begin, std::min(end, tree[li].end));
    Apply(tree, ri, std::max(begin, tree[ri].begin), end);
  }
}

int GetVal(std::vector<Node>& tree, int ci, int index) {
  Push(tree, ci);
  int li = Left(ci);
  int ri = Right(ci);

  if (tree[ci].begin == index && tree[ci].end == index + 1) {
    return tree[ci].val;
  }
  if (tree[li].end > index) {
    return GetVal(tree, li, index);
  }
  return GetVal(tree, ri, index);
}

void SolveOne(std::istream& input) {
  int n, q;
  input >> n >> q;

  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<Node> tree = BuildTree(data);

  while (q--) {
    int id;
    input >> id;
    if (id == 1) {
      int l, r;
      input >> l >> r;
      --l;
      Apply(tree, 0, l, r);
    } else {
      int index;
      input >> index;
      --index;
      std::cout << GetVal(tree, 0, index) << '\n';
    }
  }
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
5 8
1 420 69 1434 2023
1 2 3
2 2
2 3
2 4
1 2 5
2 1
2 3
2 5
2 3
9999 1000
1 1 2
2 1
2 2
1 1
1
2 1
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
