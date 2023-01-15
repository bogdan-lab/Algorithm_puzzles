#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

constexpr int ToInt(char c) {
  return static_cast<int>(c) - static_cast<int>('a');
}

constexpr char kMaxValue = 'z' + 1;

struct Node {
  Node() = default;

  Node(char c, int pos)
      : mp(ToInt(kMaxValue) + 1),
        r(c),
        l(c),
        cnt_l(1),
        cnt_r(1),
        start(pos),
        end(pos + 1) {
    mp[ToInt(c)] = 1;
  }

  Node(const Node& lhs, const Node& rhs) : mp(lhs.mp.size()) {
    assert(lhs.end == rhs.start);
    assert(lhs.mp.size() == rhs.mp.size());
    l = lhs.l;
    cnt_l = lhs.cnt_l;
    if (lhs.IsSorted() && lhs.r <= rhs.l) {
      cnt_l += rhs.cnt_l;
    }

    r = rhs.r;
    cnt_r = rhs.cnt_r;
    if (rhs.IsSorted() && rhs.l >= lhs.r) {
      cnt_r += lhs.cnt_r;
    }

    for (int i = 0; i < lhs.mp.size(); ++i) {
      mp[i] = lhs.mp[i] + rhs.mp[i];
    }

    start = lhs.start;
    end = rhs.end;
  }

  bool IsSorted() const { return end - start == std::min(cnt_l, cnt_r); }

  char r = '\0';
  int cnt_r = 1;
  char l = '\0';
  int cnt_l = 1;
  std::vector<int> mp = std::vector<int>(ToInt(kMaxValue) + 1);

  int start = 0;
  int end = 0;
};

int Left(int i) { return 2 * i + 1; }
int Right(int i) { return 2 * i + 2; }
int Parent(int i) { return (i - 1) / 2; }

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int GetPower2(int val) {
  int res = 1;
  while (res < val) {
    res *= 2;
  }
  return res;
}

std::vector<Node> BuildTree(const std::string& data) {
  int last_lvl_size = GetPower2(data.size());
  int total_size = 2 * last_lvl_size - 1;

  std::vector<Node> res(total_size);
  for (int i = last_lvl_size - 1; i < res.size(); ++i) {
    int j = i - last_lvl_size + 1;
    res[i] = j < data.size() ? Node{data[j], j} : Node{kMaxValue, j};
  }

  for (int i = last_lvl_size - 2; i >= 0; --i) {
    res[i] = Node{res[Left(i)], res[Right(i)]};
  }

  return res;
}

void SetChar(std::vector<Node>& tree, int i, char new_char) {
  int tree_index = (tree.size() + 1) / 2 + i - 1;

  tree[tree_index] = Node{new_char, i};

  while (tree_index != 0) {
    int pi = Parent(tree_index);
    tree[pi] = Node{tree[Left(pi)], tree[Right(pi)]};
    tree_index = pi;
  }
}

void AccumulateRanges(const std::vector<Node>& tree, int ci, int l, int r,
                      std::vector<Node>& rng) {
  if (ci >= tree.size() || l >= r) return;
  if (r <= tree[ci].start || l >= tree[ci].end) return;
  if (tree[ci].start == l && tree[ci].end == r) {
    rng.push_back(tree[ci]);
    return;
  }

  int li = Left(ci);
  AccumulateRanges(tree, li, l, std::min(tree[li].end, r), rng);
  int ri = Right(ci);
  AccumulateRanges(tree, ri, std::max(tree[ri].start, l), r, rng);
}

bool IsSubstring(const std::vector<Node>& data,
                 const std::vector<int>& word_mp) {
  assert(!data.empty());
  Node nd = data.front();
  for (int i = 1; i < data.size(); ++i) {
    nd = Node{nd, data[i]};
  }
  if (!nd.IsSorted()) return false;

  int start = ToInt(nd.l);
  int last = ToInt(nd.r);
  assert(nd.mp[start] > 0);
  assert(nd.mp[last] > 0);
  for (int i = start + 1; i <= last - 1; ++i) {
    if (word_mp[i] != nd.mp[i]) return false;
  }
  return true;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::string s;
  input >> s;

  std::vector<Node> tree = BuildTree(s);

  int q = 0;
  input >> q;
  while (q--) {
    int code;
    input >> code;
    if (code == 1) {
      int x;
      char new_char;
      input >> x >> new_char;
      --x;
      SetChar(tree, x, new_char);
    } else {
      int l, r;
      input >> l >> r;
      --l;
      std::vector<Node> rngs;
      AccumulateRanges(tree, 0, l, r, rngs);
      if (IsSubstring(rngs, tree[0].mp)) {
        std::cout << "Yes\n";
      } else {
        std::cout << "No\n";
      }
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
ab
9
2 1 2
1 1 b
2 1 2
1 1 c
2 1 2
1 2 c
2 1 2
1 2 d
2 1 2
)";
    Solution(ss);
    std::cout << "expected = Yes; Yes; No; Yes; Yes\n";
  }
  {
    std::stringstream ss;
    ss << R"(8
bbbabbbc
5
2 2 6
1 4 b
2 2 6
1 6 c
2 2 6
)";
    Solution(ss);
    std::cout << "expected = No; Yes; Yes\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
abbac
1
2 1 5
)";
    Solution(ss);
    std::cout << "expected =  No\n";
  }
  {
    std::stringstream ss;
    ss << R"(1
a
3
2 1 1
1 1 c
2 1 1
)";
    Solution(ss);
    std::cout << "expected = Yes; Yes\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
aaaa
4
2 1 3
2 1 2
1 2 b
2 1 3
)";
    Solution(ss);
    std::cout << "expected = Yes; Yes; No\n";
  }
  {
    std::stringstream ss;
    ss << R"(8
aaabcccb
1
2 1 7
)";
    Solution(ss);
    std::cout << "expected = No\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
abcdcf
4
2 1 3
2 2 6
1 5 e
2 2 6
)";
    Solution(ss);
    std::cout << "expected = Yes; No; Yes\n";
  }
}
