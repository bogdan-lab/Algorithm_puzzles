#include <deque>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();
std::string solve_one_case(int n);
std::string convert_to_str(const std::deque<int>& vec);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

std::string convert_to_str(const std::deque<int>& vec) {
  std::stringstream ss;
  for (auto el : vec) {
    ss << el << ' ';
  }
  return ss.str();
}

std::string solve_one_case(int n) {
  std::deque<int> res;
  std::set<int> pull = [&]() {
    std::set<int> s;
    for (int i = 1; i <= n; ++i) {
      s.insert(i);
    }
    return s;
  }();
  res.push_back(n / 2);
  pull.erase(n / 2);
  while (!pull.empty()) {
    int val = -1;
    for (auto it = pull.begin(); it != pull.end(); ++it) {
      int f_dist = std::abs(res.front() - *it);
      if (f_dist >= 2 && f_dist <= 4) {
        val = *it;
        res.push_front(*it);
        break;
      }
      int b_dist = std::abs(res.back() - *it);
      if (b_dist >= 2 && b_dist <= 4) {
        val = *it;
        res.push_back(*it);
        break;
      }
    }
    if (val == -1) {
      return "-1";
    }
    pull.erase(val);
  }
  return convert_to_str(res);
}

void solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::cout << solve_one_case(n) << '\n';
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(6
10
2
4
6
7
13
)";
    solution(ss);
    std::cout << "expected\n";
    std::cout << "9 6 10 8 4 7 3 1 5 2\n";
    std::cout << "-1\n";
    std::cout << "3 1 4 2\n";
    std::cout << "5 3 6 2 4 1\n";
    std::cout << "5 1 3 6 2 4 7\n";
    std::cout << "13 9 7 11 8 4 1 3 5 2 6 10 12\n";
  }
}
