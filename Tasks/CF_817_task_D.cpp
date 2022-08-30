#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
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

int64_t CalcInitialValue(const std::string& data) {
  int64_t res = 0;
  for (int i = 0; i < data.size(); ++i) {
    if (data[i] == 'R') {
      res += data.size() - i - 1;
    } else {
      res += i;
    }
  }
  return res;
}

std::vector<int64_t> CalcValues(const std::string& data) {
  int64_t initial_count = CalcInitialValue(data);
  std::vector<int64_t> res;
  res.reserve(data.size());

  res.push_back(initial_count);
  int lhs = 0;
  int rhs = data.size() - 1;
  while (true) {
    while (lhs < data.size() - 1 && data[lhs] == 'R') {
      ++lhs;
    }
    while (rhs > 0 && data[rhs] == 'L') {
      --rhs;
    }
    int l_change = data.size() - lhs - 1 - lhs;
    int r_change = rhs - (data.size() - rhs - 1);
    if (l_change <= 0 && r_change <= 0) {
      break;
    } else if (l_change > r_change) {
      initial_count += l_change;
      ++lhs;
    } else {
      initial_count += r_change;
      --rhs;
    }
    res.push_back(initial_count);
  }

  return res;
}

void Solution(std::istream& input) {
  int case_num;
  input >> case_num;
  while (case_num--) {
    int char_num;
    std::string buff;
    input >> char_num >> buff;
    std::vector<int64_t> res = CalcValues(buff);
    int idx = 1;
    for (int i = 0; i < buff.size(); ++i) {
      idx = std::min<int64_t>(res.size() - 1, idx);
      std::cout << res[idx] << ' ';
      ++idx;
    }
    std::cout << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
3
LLR
5
LRRLL
1
L
12
LRRRLLLRLLRL
10
LLLLLRRRRR
9
LRLRLRLRL
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
