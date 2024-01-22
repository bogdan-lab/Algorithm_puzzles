#include <array>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

constexpr int MaxNum = 500'000 + 13;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //   RunTests();
  Solution(std::cin);
  return 0;
}

int get_head(std::array<int, MaxNum>& heads, int curr) {
  if (heads[curr] == -1) return curr;
  heads[curr] = get_head(heads, heads[curr]);
  return heads[curr];
}

void merge(std::array<int, MaxNum>& heads, std::array<int, MaxNum>& counts,
           int lhs, int rhs) {
  int l_head = get_head(heads, lhs);
  int r_head = get_head(heads, rhs);
  if (l_head == r_head) return;
  if (counts[l_head] <= counts[r_head]) {
    heads[l_head] = r_head;
    counts[r_head] += counts[l_head];
  } else {
    heads[r_head] = l_head;
    counts[l_head] += counts[r_head];
  }
}

void Solution(std::istream& input) {
  int person_num, m;
  input >> person_num >> m;

  std::array<int, MaxNum> heads;
  heads.fill(-1);
  std::array<int, MaxNum> counts;
  counts.fill(1);
  for (int g = 0; g < m; ++g) {
    int count = 0;
    input >> count;
    if (count == 0) continue;
    int front = 0;
    input >> front;
    --front;
    for (int i = 1; i < count; ++i) {
      int next = 0;
      input >> next;
      --next;
      merge(heads, counts, front, next);
    }
  }

  for (int i = 0; i < person_num; ++i) {
    int head = get_head(heads, i);
    std::cout << counts[head] << ' ';
  }
  std::cout << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(
        7 5
3 2 5 4
0
2 1 2
1 1
2 6 7
    )";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
