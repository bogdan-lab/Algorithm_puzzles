#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

struct Result {
  Result(int size) : a(size, '\0'), b(size, '\0') {}
  std::string a;
  std::string b;
  bool is_valid = false;
};

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

char Opposite(char c) { return c == ')' ? '(' : ')'; }

Result BuildSequences(const std::string& data) {
  Result res(data.size());
  if (data.front() != '1' || data.back() != '1') {
    return res;
  }
  if (data.size() % 2) return res;
  res.a.front() = '(';
  res.b.front() = '(';
  res.a.back() = ')';
  res.b.back() = ')';
  int a_bal = 1;  // +1 for open and -1 for closed
  int b_bal = 1;
  for (size_t i = 1; i < data.size() - 1; ++i) {
    if (data[i] == '1') {
      if (a_bal == 0 || b_bal == 0) {
        res.a[i] = '(';
        res.b[i] = '(';
        ++a_bal;
        ++b_bal;
      } else {
        res.a[i] = ')';
        res.b[i] = ')';
        --a_bal;
        --b_bal;
      }
    } else {
      // Decrease in each
      if (a_bal == 0 && b_bal == 0) {
        return res;
      }
      if (a_bal > b_bal) {
        res.a[i] = ')';
        --a_bal;
        res.b[i] = '(';
        ++b_bal;
      } else {
        res.a[i] = '(';
        ++a_bal;
        res.b[i] = ')';
        --b_bal;
      }
    }
    if (a_bal < 0 || b_bal < 0) return res;
  }

  res.is_valid = a_bal == 1 && b_bal == 1;
  return res;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::string data;
    data.reserve(n);
    input >> data;

    Result res = BuildSequences(data);
    if (res.is_valid) {
      std::cout << "YES\n" << res.a << '\n' << res.b << '\n';
    } else {
      std::cout << "NO\n";
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
6
101101
10
1001101101
4
1100
6
110101
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
