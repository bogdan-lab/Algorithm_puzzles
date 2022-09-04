#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr uint64_t kPolCoef = 9931;

void Solution(std::istream& input = std::cin);
void RunTests();

bool CheckEquality(const std::string& text, const std::vector<uint64_t>& prefix,
                   const std::vector<uint64_t>& powers, int lb, int le, int rb,
                   int re);

bool DirectCheck(const std::string& text, int lb, int le, int rb, int re);
std::vector<uint64_t> GetCoefPowers(int num);
uint64_t ToInt(char ch);
std::vector<uint64_t> GetPrefix(const std::string& text,
                                const std::vector<uint64_t>& powers);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::string text;
  input >> text;
  std::vector<uint64_t> powers = GetCoefPowers(text.size());
  std::vector<uint64_t> prefix = GetPrefix(text, powers);
  int n;
  input >> n;
  while (n--) {
    int lb, le, rb, re;
    input >> lb >> le >> rb >> re;
    --lb;
    --rb;
    if (CheckEquality(text, prefix, powers, lb, le, rb, re)) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  }
}
std::vector<uint64_t> GetPrefix(const std::string& text,
                                const std::vector<uint64_t>& powers) {
  std::vector<uint64_t> result(text.size());
  result[0] = ToInt(text[0]);
  for (int i = 1; i < result.size(); ++i) {
    result[i] = result[i - 1] + powers[i] * ToInt(text[i]);
  }

  return result;
}

uint64_t ToInt(char ch) { return static_cast<uint64_t>(ch); }

std::vector<uint64_t> GetCoefPowers(int num) {
  std::vector<uint64_t> res(num);
  res[0] = 1;
  for (int i = 1; i < num; ++i) {
    res[i] = res[i - 1] * kPolCoef;
  }
  return res;
}

bool DirectCheck(const std::string& text, int lb, int le, int rb, int re) {
  while (lb < le) {
    if (text[lb++] != text[rb++]) {
      return false;
    }
  }
  return true;
}

bool CheckEquality(const std::string& text, const std::vector<uint64_t>& prefix,
                   const std::vector<uint64_t>& powers, int lb, int le, int rb,
                   int re) {
  if (re - rb != le - lb) {
    return false;
  }
  if (re == 0) {
    return le == lb;
  }
  if (le == 0) {
    return re == rb;
  }
  uint64_t lhs = (prefix[le - 1] - (lb == 0 ? 0 : prefix[lb - 1])) * powers[rb];
  uint64_t rhs = (prefix[re - 1] - (rb == 0 ? 0 : prefix[rb - 1])) * powers[lb];
  if (lhs != rhs) {
    return false;
  }
  if (!DirectCheck(text, lb, le, rb, re)) {
    return false;
  }
  return true;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(trololo
4
1 7 1 7
3 5 5 7
4 5 6 7 
1 1 1 5
)";
    Solution(ss);
    std::cout << "expected = Yes; Yes; Yes; No\n";
  }
}
