#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int ToInt(char c) { return static_cast<int>(c) - static_cast<int>('a'); }

int Left(int index) { return 2 * index + 1; }
int Right(int index) { return 2 * index + 2; }
int Parent(int index) { return (index - 1) / 2; }

struct Node {
  Node() = default;
  Node(int start, int end) : s(start), e(end), mp(ToInt('z') + 1) {}

  void Set(int start, int end) {
    s = start;
    e = end;
    mp.resize(ToInt('z') + 1);
  }

  void Set(char c, int start, int end) {
    s = start;
    e = end;
    mp.resize(ToInt('z') + 1);
    mp[ToInt(c)] = 1;
  }
  void Replace(char prev, char upd) {
    --mp[ToInt(prev)];
    ++mp[ToInt(upd)];
  }
  int s = 0;
  int e = 0;
  std::vector<int> mp;
};

Node Add(const Node& l, const Node& r) {
  Node res(std::min(l.s, r.s), std::max(l.e, r.e));
  for (int i = 0; i < res.mp.size(); ++i) {
    res.mp[i] = l.mp[i] + r.mp[i];
  }
  return res;
}

int GetNextPower2(int val) {
  int res = 1;
  while (res < val) {
    res *= 2;
  }
  return res;
}

void SetSymbol(int pos, char c, std::vector<Node>& range_tree,
               int last_lvl_start, std::string& buff) {
  int index = last_lvl_start + pos;
  char prev_char = buff[pos];
  buff[pos] = c;
  range_tree[index].Replace(prev_char, c);
  while (index > 0) {
    index = Parent(index);
    range_tree[index].Replace(prev_char, c);
  }
}

void GetUniqueNum(const std::vector<Node>& range_tree, int index, int start,
                  int end, std::vector<int>& mp) {
  if (index >= range_tree.size()) return;
  if (range_tree[index].s >= end || range_tree[index].e <= start) {
    return;
  }
  if (range_tree[index].s >= start && range_tree[index].e <= end) {
    for (int i = 0; i < mp.size(); ++i) {
      mp[i] += range_tree[index].mp[i];
    }
    return;
  }
  GetUniqueNum(range_tree, Left(index), start, end, mp);
  GetUniqueNum(range_tree, Right(index), start, end, mp);
}

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::string buff;
  input >> buff;
  int n;
  input >> n;

  int pow_2 = GetNextPower2(buff.size());
  std::vector<Node> range_tree(2 * pow_2 - 1);

  int last_lvl_start = pow_2 - 1;
  for (int i = range_tree.size() - 1; i >= last_lvl_start; --i) {
    int pos = i - last_lvl_start;
    if (pos >= buff.size()) {
      range_tree[i].Set(pos, pos + 1);
    } else {
      range_tree[i].Set(buff[pos], pos, pos + 1);
    }
  }

  for (int i = last_lvl_start - 1; i >= 0; --i) {
    range_tree[i] = Add(range_tree[Left(i)], range_tree[Right(i)]);
  }

  int type = 0;
  while (n--) {
    input >> type;
    switch (type) {
      case 1: {
        int pos;
        char c;
        input >> pos >> c;
        SetSymbol(--pos, c, range_tree, last_lvl_start, buff);
        break;
      }
      case 2: {
        int l, r;
        input >> l >> r;
        --l;
        std::vector<int> mp(ToInt('z') + 1);
        GetUniqueNum(range_tree, 0, l, r, mp);
        int count = std::count_if(mp.begin(), mp.end(),
                                  [](int val) { return val != 0; });
        std::cout << count << '\n';
        break;
      }
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(abacaba
5
2 1 4
1 4 b
1 5 b
2 4 6
2 1 7
)";
    Solution(ss);
    std::cout << "expected = 3; 1; 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(dfcbbcfeeedbaea
15
1 6 e
1 4 b
2 6 14
1 7 b
1 12 c
2 6 8
2 1 6
1 7 c
1 2 f
1 10 a
2 7 9
1 10 a
1 14 b
1 1 f
2 1 11
)";
    Solution(ss);
    std::cout << "expected = 5; 2; 5; 2; 6\n";
  }
}
