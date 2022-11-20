#include <cassert>
#include <limits>
#include <tuple>
#include <vector>

int Left(int i) { return 2 * i + 1; }
int Right(int i) { return 2 * (i + 1); }
int Parent(int i) { return (i - 1) / 2; }

struct Node {
  int max_val = std::numeric_limits<int>::min();
  int max_index = 0;
  int l = 0;
  int r = 0;
};

struct SearchRes {
  SearchRes() = default;
  SearchRes(const Node& n) : max_val(n.max_val), max_index(n.max_index) {}

  int max_val = std::numeric_limits<int>::min();
  int max_index = 0;
};

SearchRes Merge(SearchRes l, SearchRes r) {
  if (std::tie(l.max_val, l.max_index) < std::tie(r.max_val, r.max_index)) {
    return r;
  }
  return l;
}

Node Merge(Node l, Node r) {
  Node res;
  res.l = l.l;
  res.r = r.r;
  if (std::tie(l.max_val, l.max_index) > std::tie(r.max_val, r.max_index)) {
    res.max_val = l.max_val;
    res.max_index = l.max_index;
  } else {
    res.max_val = r.max_val;
    res.max_index = r.max_index;
  }
  return res;
}

void DeleteElement(std::vector<Node>& data, int index) {
  int i = index + (data.size() + 1) / 2 - 1;
  data[i].max_val = std::numeric_limits<int>::min();
  while (i > 0) {
    int p = Parent(i);
    int l = Left(p);
    int r = Right(p);
    data[p] = Merge(data[l], data[r]);
    i = p;
  }
}

int GetRightPower(int val) {
  int res = 1;
  while (res < val) {
    res *= 2;
  }
  return res;
}

std::vector<Node> BuildSegmentTree(const std::vector<int>& score) {
  int pw = GetRightPower(score.size());
  int tree_size = 2 * pw - 1;
  std::vector<Node> data(tree_size);
  int i = pw - 1;
  for (int i = pw - 1; i < data.size(); ++i) {
    int j = i - pw + 1;
    data[i].l = j;
    data[i].r = j + 1;
    data[i].max_index = j;
    data[i].max_val =
        j < score.size() ? score[j] : std::numeric_limits<int>::min();
  }
  for (int i = data.size() - 1; i > 0; i -= 2) {
    data[Parent(i)] = Merge(data[i - 1], data[i]);
  }

  return data;
}

SearchRes GetMax(const std::vector<Node>& data, int pos, int start, int end) {
  if (data[pos].l >= end || data[pos].r <= start) return {};
  if (data[pos].l == start && data[pos].r == end) return {data[pos]};
  int l = Left(pos);
  SearchRes lhs;
  if (data[l].r > start) {
    lhs = GetMax(data, l, start, std::min(end, data[l].r));
  }
  int r = Right(pos);
  SearchRes rhs;
  if (data[r].l < end) {
    rhs = GetMax(data, r, std::max(data[r].l, start), end);
  }
  return Merge(lhs, rhs);
}

class Solution {
 public:
  long teamFormation(std::vector<int> score, int team_size, int k) {
    std::vector<Node> tree = BuildSegmentTree(score);
    int p_max_k = k;
    int s_min_k = score.size() > k ? score.size() - k : 0;

    long total = 0;
    for (int i = 0; i < team_size; ++i) {
      SearchRes prefix = GetMax(tree, 0, 0, p_max_k);
      SearchRes suffix = GetMax(tree, 0, s_min_k, score.size());
      if (std::tie(prefix.max_val, prefix.max_index) >
          std::tie(suffix.max_val, suffix.max_index)) {
        total += prefix.max_val;
        DeleteElement(tree, prefix.max_index);
        p_max_k = std::min<int>(p_max_k + 1, score.size());
      } else {
        total += suffix.max_val;
        DeleteElement(tree, suffix.max_index);
        s_min_k = std::max(0, s_min_k - 1);
      }
    }
    return total;
  }
};

int main() {
  Solution s;

  assert(s.teamFormation({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 1) == 34);
  assert(s.teamFormation({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 2) == 34);
  assert(s.teamFormation({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 3) == 34);
  assert(s.teamFormation({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 4) == 34);
  assert(s.teamFormation({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 5) == 34);
  assert(s.teamFormation({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 6) == 34);
  assert(s.teamFormation({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 7) == 34);
  assert(s.teamFormation({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 8) == 34);
  assert(s.teamFormation({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 9) == 34);
  assert(s.teamFormation({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 10) == 34);

  assert(s.teamFormation({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4, 1) == 34);
  assert(s.teamFormation({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4, 2) == 34);
  assert(s.teamFormation({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4, 3) == 34);
  assert(s.teamFormation({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4, 4) == 34);
  assert(s.teamFormation({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4, 5) == 34);
  assert(s.teamFormation({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4, 6) == 34);
  assert(s.teamFormation({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4, 7) == 34);
  assert(s.teamFormation({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4, 8) == 34);
  assert(s.teamFormation({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4, 9) == 34);
  assert(s.teamFormation({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4, 10) == 34);

  assert(s.teamFormation({0, 0, 10, 9, 8, 10, 0, 0}, 3, 3) == 29);

  return 0;
}
