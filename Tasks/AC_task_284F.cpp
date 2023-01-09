#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

constexpr int kMax = 1'000'000;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int CountEqual(const std::string& w, int l, int r) {
  int count = 0;
  for (int i = l, j = r; j < w.size(); ++i, ++j) {
    if (w[i] != w[j]) break;
    ++count;
  }
  return count;
}

std::vector<int> BuildZArray(const std::string& w) {
  assert(w.size() >= 2);
  std::vector<int> z(w.size());
  z[0] = -1;
  int eqc = CountEqual(w, 0, 1);
  int l = 1;
  int r = l + eqc;
  z[1] = eqc;
  for (int i = 2; i < w.size(); ++i) {
    if (i > l && i < r) {
      int ppos = i - l;
      if (z[ppos] < r - i) {
        z[i] = z[ppos];
      } else {
        eqc = CountEqual(w, z[ppos], r);
        z[i] = z[ppos] + eqc;
        l = i;
        r = l + z[i];
      }
    } else {
      eqc = CountEqual(w, 0, i);
      z[i] = eqc;
      l = i;
      r = l + z[i];
    }
    z[i] = std::min<int>(z[i], w.size() - i);
  }

  return z;
}

std::vector<int> CountZArray(const std::vector<int>& z) {
  std::vector<int> count(kMax + 1);
  for (int i = 1; i < z.size(); ++i) {
    if (z[i] == z.size() - i) {
      count[z[i]] = 1;
    }
  }
  return count;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::string word;
  input >> word;

  std::string rhs = word;
  std::reverse(rhs.begin() + n, rhs.end());

  std::string lhs = word;
  std::reverse(lhs.begin(), lhs.begin() + n);

  std::vector<int> rz = BuildZArray(rhs);
  std::vector<int> lz = BuildZArray(lhs);

  std::vector<int> cr = CountZArray(rz);
  std::vector<int> cl = CountZArray(lz);

  cr[0] = cl[0] = 1;

  for (int i = 0; i <= n; ++i) {
    if (cr[i] && cl[n - i]) {
      std::string res = word.substr(i, n);
      std::reverse(res.begin(), res.end());
      std::cout << res << '\n' << i << '\n';
      return;
    }
  }
  std::cout << "-1\n";
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
abcbac
)";
    Solution(ss);
    std::cout << "expected = abc; 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
abababab
)";
    Solution(ss);
    std::cout << "expected = abab; 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
agccga
)";
    Solution(ss);
    std::cout << "expected = cga; 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
atcodeer
)";
    Solution(ss);
    std::cout << "expected = -1\n";
  }
}
