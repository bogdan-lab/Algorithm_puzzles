#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();
bool check_permutaiton(std::vector<int>& shifts);
size_t mod(int val, int base);
int get_new_pos(int k, int n);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    size_t n;
    input >> n;
    std::vector<int> shifts(n);
    for (size_t i = 0; i < n; ++i) {
      input >> shifts[i];
    }
    std::cout << (check_permutaiton(shifts) ? "YES\n" : "NO\n");
  }
}

size_t mod(int val, int base) {
  if (val >= 0) return val % base;
  int res = val % base;
  if (res) return res + base;
  return res;
}

int get_new_pos(int k, int n) { return mod(k, n); }

bool check_permutaiton(std::vector<int>& shifts) {
  std::vector<int> filled_flags(shifts.size());
  for (int i = 0; i < shifts.size(); ++i) {
    size_t pos = mod(i + shifts[i], shifts.size());
    if (filled_flags[pos]) {
      return false;
    }
    filled_flags[pos] = 1;
  }
  return true;
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(6
1
14
2
1 -1
4
5 5 5 1
3
3 2 1
2
0 1
5
-239 -2 -100 -3 -11
)";
    solution(ss);
    std::cout << "expected = YES YES YES NO NO YES\n";
  }
}
