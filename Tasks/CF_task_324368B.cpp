#include <iostream>
#include <sstream>
#include <vector>

using Table =
    std::vector<std::vector<std::vector<std::vector<std::vector<int64_t>>>>>;

void Solution(std::istream& input = std::cin);
void RunTests();

Table Create(int n1, int n2, int n3, int n4, int n5) {
  Table res(n1);
  for (auto& el2 : res) {
    el2.resize(n2);
    for (auto& el3 : el2) {
      el3.resize(n3);
      for (auto& el4 : el3) {
        el4.resize(n4);
        for (auto& el5 : el4) {
          el5.resize(n5);
        }
      }
    }
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n1, n2, n3, n4, n5;
  input >> n1 >> n2 >> n3 >> n4 >> n5;

  Table data = Create(n1, n2, n3, n4, n5);

  for (int i1 = 0; i1 < n1; ++i1) {
    for (int i2 = 0; i2 < n2; ++i2) {
      for (int i3 = 0; i3 < n3; ++i3) {
        for (int i4 = 0; i4 < n4; ++i4) {
          for (int i5 = 0; i5 < n5; ++i5) {
            input >> data[i1][i2][i3][i4][i5];
          }
        }
      }
    }
  }

  Table prefix = Create(n1 + 1, n2 + 1, n3 + 1, n4 + 1, n5 + 1);
  for (int i1 = 0; i1 < n1; ++i1) {
    for (int i2 = 0; i2 < n2; ++i2) {
      for (int i3 = 0; i3 < n3; ++i3) {
        for (int i4 = 0; i4 < n4; ++i4) {
          for (int i5 = 0; i5 < n5; ++i5) {
            prefix[i1 + 1][i2 + 1][i3 + 1][i4 + 1][i5 + 1] =
                prefix[i1][i2 + 1][i3 + 1][i4 + 1][i5 + 1] +
                prefix[i1 + 1][i2][i3 + 1][i4 + 1][i5 + 1] +
                prefix[i1 + 1][i2 + 1][i3][i4 + 1][i5 + 1] +
                prefix[i1 + 1][i2 + 1][i3 + 1][i4][i5 + 1] +
                prefix[i1 + 1][i2 + 1][i3 + 1][i4 + 1][i5] -
                prefix[i1][i2][i3 + 1][i4 + 1][i5 + 1] -
                prefix[i1][i2 + 1][i3][i4 + 1][i5 + 1] -
                prefix[i1][i2 + 1][i3 + 1][i4][i5 + 1] -
                prefix[i1][i2 + 1][i3 + 1][i4 + 1][i5] -
                prefix[i1 + 1][i2][i3][i4 + 1][i5 + 1] -
                prefix[i1 + 1][i2][i3 + 1][i4][i5 + 1] -
                prefix[i1 + 1][i2][i3 + 1][i4 + 1][i5] -
                prefix[i1 + 1][i2 + 1][i3][i4][i5 + 1] -
                prefix[i1 + 1][i2 + 1][i3][i4 + 1][i5] -
                prefix[i1 + 1][i2 + 1][i3 + 1][i4][i5] +
                prefix[i1][i2][i3][i4 + 1][i5 + 1] +
                prefix[i1][i2][i3 + 1][i4][i5 + 1] +
                prefix[i1][i2][i3 + 1][i4 + 1][i5] +
                prefix[i1][i2 + 1][i3][i4][i5 + 1] +
                prefix[i1][i2 + 1][i3][i4 + 1][i5] +
                prefix[i1][i2 + 1][i3 + 1][i4][i5] +
                prefix[i1 + 1][i2][i3][i4][i5 + 1] +
                prefix[i1 + 1][i2][i3][i4 + 1][i5] +
                prefix[i1 + 1][i2][i3 + 1][i4][i5] +
                prefix[i1 + 1][i2 + 1][i3][i4][i5] -
                prefix[i1][i2][i3][i4][i5 + 1] -
                prefix[i1][i2][i3][i4 + 1][i5] -
                prefix[i1][i2][i3 + 1][i4][i5] -
                prefix[i1][i2 + 1][i3][i4][i5] -
                prefix[i1 + 1][i2][i3][i4][i5] + prefix[i1][i2][i3][i4][i5] +
                data[i1][i2][i3][i4][i5];
          }
        }
      }
    }
  }

  int q = 0;
  input >> q;
  while (q--) {
    int l1, l2, l3, l4, l5;
    int r1, r2, r3, r4, r5;

    input >> l1 >> l2 >> l3 >> l4 >> l5 >> r1 >> r2 >> r3 >> r4 >> r5;
    --l1;
    --l2;
    --l3;
    --l4;
    --l5;

    int64_t res = prefix[r1][r2][r3][r4][r5] - prefix[l1][r2][r3][r4][r5] -
                  prefix[r1][l2][r3][r4][r5] - prefix[r1][r2][l3][r4][r5] -
                  prefix[r1][r2][r3][l4][r5] - prefix[r1][r2][r3][r4][l5] +
                  prefix[l1][l2][r3][r4][r5] + prefix[l1][r2][l3][r4][r5] +
                  prefix[l1][r2][r3][l4][r5] + prefix[l1][r2][r3][r4][l5] +
                  prefix[r1][l2][l3][r4][r5] + prefix[r1][l2][r3][l4][r5] +
                  prefix[r1][l2][r3][r4][l5] + prefix[r1][r2][l3][l4][r5] +
                  prefix[r1][r2][l3][r4][l5] + prefix[r1][r2][r3][l4][l5] -
                  prefix[l1][l2][l3][r4][r5] - prefix[l1][l2][r3][l4][r5] -
                  prefix[l1][l2][r3][r4][l5] - prefix[l1][r2][l3][l4][r5] -
                  prefix[l1][r2][l3][r4][l5] - prefix[l1][r2][r3][l4][l5] -
                  prefix[r1][l2][l3][l4][r5] - prefix[r1][l2][l3][r4][l5] -
                  prefix[r1][l2][r3][l4][l5] - prefix[r1][r2][l3][l4][l5] +
                  prefix[l1][l2][l3][l4][r5] + prefix[l1][l2][l3][r4][l5] +
                  prefix[l1][l2][r3][l4][l5] + prefix[l1][r2][l3][l4][l5] +
                  prefix[r1][l2][l3][l4][l5] - prefix[l1][l2][l3][l4][l5];
    std::cout << res << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(1 1 1 1 1
17
1
1 1 1 1 1 1 1 1 1 1
)";
    Solution(ss);
    std::cout << "expected = 17\n";
  }
  {
    std::stringstream ss;
    ss << R"(2 2 2 2 2
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
3
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 2 2 2 2 2
1 2 1 2 1 1 2 1 2 1
)";
    Solution(ss);
    std::cout << "expected = 1; 32; 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(2 2 2 2 2
1 2
3 4
5 6
7 8
9 10
11 12
13 14
15 16
17 18
19 20
21 22
23 24
25 26
27 28
29 30
31 32
3
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 2 2 2 2 2
1 2 1 2 1 1 2 1 2 1
)";
    Solution(ss);
    std::cout << "expected = 1; 528; 11\n";
  }
}
