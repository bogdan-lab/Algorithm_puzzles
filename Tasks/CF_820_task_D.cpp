#include <algorithm>
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

bool CheckSolution(const std::vector<int>& diff, int val) {
  int first = diff.size() - 2 * val;
  if (first < 0) return false;
  int last = diff.size() - 1;
  while (first < last) {
    if (diff[last] + diff[first] < 0) {
      return false;
    }
    --last;
    ++first;
  }
  return true;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::vector<int> spend(n);
    for (auto& el : spend) {
      input >> el;
    }
    std::vector<int> budget(n);
    for (auto& el : budget) {
      input >> el;
    }

    std::vector<int> diff(n);
    for (int i = 0; i < n; ++i) {
      diff[i] = budget[i] - spend[i];
    }

    std::sort(diff.begin(), diff.end());

    int l = 0;
    int r = diff.size();
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (CheckSolution(diff, mid)) {
        l = mid;
      } else {
        r = mid;
      }
    }
    std::cout << l << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
6
8 3 9 2 4 5
5 3 1 4 5 10
4
1 2 3 4
1 1 2 2
3
2 3 7
1 3 10
6
2 3 6 9 5 7
3 2 7 10 6 10
6
5 4 2 1 8 100
1 1 1 1 1 200
6
1 4 1 2 4 2
1 3 3 2 3 4
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
