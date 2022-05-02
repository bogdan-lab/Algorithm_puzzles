#include <iostream>
#include <sstream>
#include <vector>

bool FillBVec(std::vector<int> a);

bool CheckInvariant(const std::vector<int>& lhs, const std::vector<int>& rhs);

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
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::vector<int> a(n);
    for (auto& el : a) {
      input >> el;
    }
    bool res = FillBVec(a);
    std::cout << (res ? "YES\n" : "NO\n");
  }
}

bool FillBVec(std::vector<int> a) {
  std::vector<int> b_left;
  std::vector<int> b_right;
  b_left.reserve(a.size());
  b_right.reserve(a.size());
  while (!a.empty()) {
    int cur_val = a.back();
    a.pop_back();
    int cur_size = b_left.size() + b_right.size();
    if ((cur_size % 2)) {
      if (b_left.size() > b_right.size()) {
        b_right.push_back(cur_val);
      } else {
        b_left.push_back(cur_val);
      }
      // here cannot be equal
    } else {
      // does not matter where to put, next step can swap
      b_right.push_back(cur_val);
    }
    if (!CheckInvariant(b_left, b_right)) {
      return false;
    }
  }
  return true;
}

bool CheckInvariant(const std::vector<int>& lhs, const std::vector<int>& rhs) {
  if (lhs.empty() || rhs.empty()) return true;
  int curr_size = lhs.size() + rhs.size();
  if (curr_size % 2) {
    if (lhs.size() > rhs.size()) {
      return lhs.back() <= rhs.back() && lhs.back() <= lhs[lhs.size() - 2];
    } else {
      return rhs.back() <= lhs.back() && rhs.back() <= rhs[rhs.size() - 2];
    }
  } else {
    if (curr_size == 2) {
      return true;
    } else {
      int p_lhs = lhs[lhs.size() - 2];
      int p_rhs = rhs[rhs.size() - 2];
      int c_lhs = lhs.back();
      int c_rhs = rhs.back();
      bool good_1 = (c_lhs <= c_rhs && c_lhs <= p_rhs && c_lhs <= p_lhs &&
                     c_rhs <= p_rhs && c_rhs <= p_lhs);
      bool good_2 = (c_rhs <= c_lhs && c_rhs <= p_lhs && c_rhs <= p_rhs &&
                     c_lhs <= p_lhs && c_lhs <= p_rhs);
      return good_1 || good_2;
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
4
3 1 5 3
3
3 2 1
1
7331
)";
    Solution(ss);
    std::cout << "expected = YES; NO; YES\n";
  }
}
