#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int GetMaxNumber(const std::vector<int>& data);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::cout << GetMaxNumber(data) << '\n';
  }
}

int GetMaxNumber(const std::vector<int>& data) {
  int li = 1;
  int lw = data.front();
  int lc = 1;
  int ri = data.size() - 1;
  int rw = 0;
  int rc = 0;
  int last_ans = 0;
  while (li <= ri) {
    while (li <= ri && rw < lw) {
      rw += data[ri];
      ri--;
      rc++;
    }
    if (lw == rw) {
      last_ans = lc + rc;
      if (li <= ri) {
        rw += data[ri];
        ri--;
        rc++;
      }
    }
    while (li <= ri && lw < rw) {
      lw += data[li];
      li++;
      lc++;
    }
    if (lw == rw) {
      last_ans = lc + rc;
      if (li <= ri) {
        lw += data[li];
        li++;
        lc++;
      }
    }
  }
  return last_ans;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
3
10 20 10
6
2 1 4 2 4 1
5
1 2 4 8 16
9
7 3 20 5 15 1 11 8 10
)";
    Solution(ss);
    std::cout << "expected = 2; 6; 0; 7\n";
  }
}
