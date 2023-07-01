#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct S {
  size_t index;
  int val;
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

struct Compare {
  bool operator()(const S& l, const S& r) const { return l.index < r.index; }
};

uint64_t GetVal(const S& m, const S& e, const S& x) {
  std::vector<int8_t> lookup{0, 0, 0, 0};
  lookup[m.val] = 1;
  lookup[e.val] = 1;
  lookup[x.val] = 1;
  return std::find(lookup.begin(), lookup.end(), 0) - lookup.begin();
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> vals(n);
  for (auto& el : vals) {
    input >> el;
  }
  std::string letters;
  input >> letters;

  std::vector<S> m;
  m.reserve(n);
  std::vector<S> e;
  e.reserve(n);
  std::vector<S> x;
  x.reserve(n);

  for (size_t i = 0; i < vals.size(); ++i) {
    switch (letters[i]) {
      case 'M': {
        m.push_back({i, vals[i]});
        break;
      }
      case 'E': {
        e.push_back({i, vals[i]});
        break;
      }
      case 'X': {
        x.push_back({i, vals[i]});
        break;
      }
    }
  }

  uint64_t res = 0;
  for (size_t i = 0; i < m.size(); ++i) {
    auto e_it = std::lower_bound(e.begin(), e.end(), m[i], Compare{});
    for (auto it = e_it; it != e.end(); ++it) {
      auto x_it = std::lower_bound(x.begin(), x.end(), *it, Compare{});
      for (auto jt = x_it; jt != x.end(); ++jt) {
        res += GetVal(m[i], *it, *jt);
      }
    }
  }
  std::cout << res << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
