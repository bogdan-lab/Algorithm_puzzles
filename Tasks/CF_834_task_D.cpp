#include <iostream>
#include <sstream>
#include <vector>

struct NumRepr {
  int two = 0;
  int five = 0;
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

NumRepr GetNumRepr(int64_t val) {
  NumRepr res;
  while (!(val % 5)) {
    val /= 5;
    ++res.five;
  }
  while (!(val % 2)) {
    val /= 2;
    ++res.two;
  }
  return res;
}

int64_t GetNewPrice(int64_t n, int64_t m) {
  NumRepr n_repr = GetNumRepr(n);

  int64_t mult = 1;

  while (n_repr.two != n_repr.five) {
    if (n_repr.two < n_repr.five) {
      if (mult * 2 <= m) {
        mult *= 2;
        ++n_repr.two;
      } else {
        break;
      }
    } else {
      if (mult * 5 <= m) {
        mult *= 5;
        ++n_repr.five;
      } else {
        break;
      }
    }
  }

  while (mult * 10 <= m) {
    mult *= 10;
  }

  return (m / mult) * mult * n;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int64_t n, m;
    input >> n >> m;
    std::cout << GetNewPrice(n, m) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(10
6 11
5 43
13 5
4 16
10050 12345
2 6
4 30
25 10
2 81
1 7
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
