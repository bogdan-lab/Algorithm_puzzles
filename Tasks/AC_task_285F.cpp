#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

struct Node {
  char r = '\0';
  int cnt_r = 1;
  char l = '\0';
  int cnt_l = 1;
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

int ToInt(char c) { return static_cast<int>(c) - static_cast<int>('a'); }

Node Merge(const Node& l, const Node& r) {
  Node res;
  res.l = l.l;
  res.cnt_l = l.cnt_l;
  if (l.end - l.start == l.cnt_l && l.r <= r.l) {
    res.cnt_l += r.cnt_l;
  }

  res.r = r.r;
  res.cnt_r = r.cnt_r;
  if (r.cnt_r == r.end - r.start && r.l >= l.r) {
    res.cnt_r += l.cnt_r;
  }

  res.start = l.start;
  res.end = r.end;
  return res;
}

std::vector<Node> BuildTree(const std::string& data) {
  int last_lvl_size = GetPower2(data.size());
  int total_size = 2 * last_lvl_size - 1;

  std::vector<Node> res(total_size);
  for (int i = last_lvl_size - 1; i < res.size(); ++i) {
    int j = i - last_lvl_size + 1;
    if (j < data.size()) {
      res[i].l = res[i].r = data[j];
    }
    res[i].cnt_l = res[i].cnt_r = 1;
    res[i].start = j;
    res[i].end = res[i].start + 1;
  }

  for (int i = last_lvl_size - 2; i >= 0; --i) {
    res[i] = Merge(res[Left(i)], res[Right(i)]);
  }

  return res;
}

void SetChar(std::vector<Node>& tree, int i, char new_char) {
  int tree_index = (tree.size() + 1) / 2 + i - 1;

  tree[tree_index].l = new_char;
  tree[tree_index].r = new_char;

  while (tree_index != 0) {
    int pi = Parent(tree_index);
    tree[pi] = Merge(tree[Left(pi)], tree[Right(pi)]);
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

bool IsSorted(const Node& node) { return node.end - node.start == node.cnt_l; }

bool IsSubstring(const std::vector<Node>& data,
                 const std::vector<int>& word_mp) {
  assert(!data.empty());
  Node nd = data.front();
  for (int i = 1; i < data.size(); ++i) {
    nd = Merge(nd, data[i]);
  }
  if (!IsSorted(nd)) return false;

  if (nd.l == nd.r) {
    return true;
  }

  int necc_count = 0;
  for (int i = ToInt(nd.l) + 1; i <= ToInt(nd.r) - 1; ++i) {
    necc_count += word_mp[i];
  }

  // the string has to have at least 1 of left char and 1 of right char
  // but it can have any OTHER number of edge characters
  return nd.cnt_l >= necc_count + 2;
}

std::vector<int> BuildWordMp(const std::string& s) {
  std::vector<int> res(ToInt('z') + 1);
  for (const auto& el : s) {
    ++res[ToInt(el)];
  }
  return res;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::string s;
  input >> s;

  std::vector<Node> tree = BuildTree(s);
  std::vector<int> word_mp = BuildWordMp(s);

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
      char old_char = s[x];
      --word_mp[ToInt(old_char)];
      ++word_mp[ToInt(new_char)];
      SetChar(tree, x, new_char);
    } else {
      int l, r;
      input >> l >> r;
      --l;
      std::vector<Node> rngs;
      AccumulateRanges(tree, 0, l, r, rngs);
      if (IsSubstring(rngs, word_mp)) {
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
    ss << R"(6
abcdcf
4
2 1 3
2 2 6
1 5 e
2 2 6
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
abcdef
21
2 1 1
2 2 2
2 3 3 
2 4 4
2 5 5
2 6 6
2 1 2
2 1 3
2 1 4
2 1 5
2 1 6
2 2 3
2 2 4
2 2 5
2 2 6
2 3 4
2 3 5
2 3 6
2 4 5
2 4 6
2 5 6
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
fedcba
21
2 1 1
2 2 2
2 3 3 
2 4 4
2 5 5
2 6 6
2 1 2
2 1 3
2 1 4
2 1 5
2 1 6
2 2 3
2 2 4
2 2 5
2 2 6
2 3 4
2 3 5
2 3 6
2 4 5
2 4 6
2 5 6
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
fedcba
48
2 1 1
2 2 2
2 3 3 
2 4 4
2 5 5
2 6 6
2 1 2
2 1 3
2 1 4
2 1 5
2 1 6
2 2 3
2 2 4
2 2 5
2 2 6
2 3 4
2 3 5
2 3 6
2 4 5
2 4 6
2 5 6

1 1 a
1 2 b
1 3 c
1 4 d
1 5 e
1 6 f

2 1 1
2 2 2
2 3 3 
2 4 4
2 5 5
2 6 6
2 1 2
2 1 3
2 1 4
2 1 5
2 1 6
2 2 3
2 2 4
2 2 5
2 2 6
2 3 4
2 3 5
2 3 6
2 4 5
2 4 6
2 5 6
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
