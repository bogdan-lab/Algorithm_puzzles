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

bool Check(const std::vector<int>& data, int s) {
  int max_val = *std::max_element(data.begin(), data.end());
  std::vector<int> lookup(max_val + 1);
  for (const auto& el : data) {
    lookup[el]++;
  }

  int req_sum = 0;
  for (int i = 0; i < lookup.size(); ++i) {
    if (lookup[i] == 0) {
      req_sum += i;
    } else if (lookup[i] == 1) {
      // do nothing
    } else {
      return false;
    }
  }
  if (req_sum > s) return false;
  int next_val = max_val + 1;
  while (req_sum < s) {
    req_sum += next_val;
    ++next_val;
  }
  return req_sum == s;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int m, s;
    input >> m >> s;
    std::vector<int> data(m);
    for (auto& el : data) {
      input >> el;
    }

    if (Check(data, s)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
3 13
3 1 4
1 1
1
3 3
1 4 2
2 1
4 3
5 6
1 2 3 4 5
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
