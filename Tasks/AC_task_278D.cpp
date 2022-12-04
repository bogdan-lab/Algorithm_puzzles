#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

int Parent(int i) { return (i - 1) / 2; }

int Left(int i) { return 2 * i + 1; }

int Right(int i) { return 2 * (i + 1); }

constexpr int kEmpty = std::numeric_limits<int>::min();

struct Node {
  int64_t val = kEmpty;
  int begin = 0;
  int end = 0;
};

int64_t GetPower2(int64_t val) {
  int64_t res = 1;
  while (res < val) {
    res *= 2;
  }
  return res;
}

std::vector<Node> BuildTree(const std::vector<int64_t>& data) {
  int64_t pow = GetPower2(data.size());
  int64_t full_size = 2 * pow - 1;
  int64_t start = pow - 1;
  std::vector<Node> res(full_size);
  for (int i = start; i < full_size; ++i) {
    int j = i - start;
    if (j < data.size()) {
      res[i].val = data[j];
    }
    res[i].begin = j;
    res[i].end = j + 1;
  }
  for (int i = start - 1; i >= 0; --i) {
    int l = Left(i);
    int r = Right(i);
    res[i].begin = res[l].begin;
    res[i].end = res[r].end;
  }
  return res;
}

void SetAllTo(std::vector<Node>& data, int64_t val) { data[0].val = val; }

void AddToVal(std::vector<Node>& data, int i, int64_t add) {
  int ci = 0;
  while (true) {
    int l = Left(ci);
    int r = Right(ci);
    if (data[ci].val != kEmpty && l < data.size() && r < data.size()) {
      data[l].val = data[ci].val;
      data[r].val = data[ci].val;
      data[ci].val = kEmpty;
    }
    if (data[ci].begin == i && data[ci].end == i + 1) {
      data[ci].val += add;
      break;
    } else {
      if (i >= data[l].begin && i < data[l].end) {
        ci = l;
      } else {
        ci = r;
      }
    }
  }
}

void PrintVal(std::vector<Node>& data, int i) {
  int ci = 0;
  while (true) {
    int l = Left(ci);
    int r = Right(ci);
    if (data[ci].val != kEmpty && l < data.size() && r < data.size()) {
      data[l].val = data[ci].val;
      data[r].val = data[ci].val;
      data[ci].val = kEmpty;
    }
    if (data[ci].begin == i && data[ci].end == i + 1) {
      std::cout << data[ci].val << '\n';
      break;
    } else {
      if (i >= data[l].begin && i < data[l].end) {
        ci = l;
      } else {
        ci = r;
      }
    }
  }
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
  int n;
  input >> n;
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<Node> buff = BuildTree(data);

  int q;
  input >> q;
  while (q--) {
    int t;
    input >> t;
    switch (t) {
      case 1: {
        int64_t x;
        input >> x;
        SetAllTo(buff, x);
        break;
      }
      case 2: {
        int64_t x;
        int i;
        input >> i >> x;
        --i;
        AddToVal(buff, i, x);
        break;
      }
      case 3: {
        int i;
        input >> i;
        --i;
        PrintVal(buff, i);
        break;
      }
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(10
1 8 4 15 7 5 7 5 8 0
20
2 7 0
3 7
3 8
1 7
3 3
2 4 4
2 4 9
2 10 5
1 10
2 4 2
1 10
2 3 1
2 8 11
2 3 14
2 1 9
3 8
3 8
3 1
2 6 5
3 7
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
