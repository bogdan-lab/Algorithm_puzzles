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
  // RunTests();
  Solution(std::cin);
  return 0;
}

char Opposite(char c) { return c == ')' ? '(' : ')'; }

Result BuildSequences(const std::string& data) {
  Result res(data.size());
  if (data.front() != '1' || data.back() != '1') {
    return res;
  }
  if (data.size() % 2) return res;
  size_t one_count = std::count(data.begin(), data.end(), '1');
  if (one_count % 2) return res;
  size_t curr_count = 0;
  char prev_a = ')';
  char prev_b = '(';
  for (size_t i = 0; i < data.size(); ++i) {
    if (data[i] == '1') {
      if (curr_count < one_count / 2) {
        res.a[i] = '(';
        res.b[i] = '(';
      } else {
        res.a[i] = ')';
        res.b[i] = ')';
      }
      ++curr_count;
    } else {
      res.a[i] = std::exchange(prev_a, Opposite(prev_a));
      res.b[i] = std::exchange(prev_b, Opposite(prev_b));
    }
  }
  res.is_valid = true;
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
