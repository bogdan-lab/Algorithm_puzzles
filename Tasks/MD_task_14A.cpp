#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr int64_t kPolCoef = 9931;
constexpr int64_t kModVal = 1000'000'000'03;

void Solution(std::istream& input = std::cin);
void RunTests();

bool CheckEquality(const std::string& text, const std::vector<int64_t>& prefix,
                   const std::vector<int64_t>& powers, int lb, int le, int rb,
                   int re);

int64_t GetHash(const std::vector<int64_t>& prefix,
                const std::vector<int64_t>& powers, int64_t s_char, int s,
                int e);
bool DirectCheck(const std::string& text, int lb, int le, int rb, int re);
std::vector<int64_t> GetCoefPowers(int num);
int64_t ToInt(char ch);
std::vector<int64_t> GetPrefix(const std::string& text);

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
  std::vector<int64_t> powers = GetCoefPowers(text.size());
  std::vector<int64_t> prefix = GetPrefix(text);
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
std::vector<int64_t> GetPrefix(const std::string& text) {
  std::vector<int64_t> result(text.size());
  result[0] = ToInt(text[0]);
  for (int i = 1; i < result.size(); ++i) {
    result[i] = (kPolCoef * result[i - 1] % kModVal + ToInt(text[i])) % kModVal;
  }

  return result;
}

int64_t ToInt(char ch) { return static_cast<int64_t>(ch); }

std::vector<int64_t> GetCoefPowers(int num) {
  std::vector<int64_t> res(num);
  res[0] = 1;
  for (int i = 1; i < num; ++i) {
    res[i] = (res[i - 1] * kPolCoef) % kModVal;
  }
  return res;
}

int64_t GetHash(const std::vector<int64_t>& prefix,
                const std::vector<int64_t>& powers, int64_t s_char, int s,
                int e) {
  if (e == s) return 0;
  int64_t rhs = (powers[e - s - 1] * (prefix[s] - s_char)) % kModVal;
  int64_t result = prefix[e - 1] - rhs;
  return result > 0 ? result : result + kModVal;
}

bool DirectCheck(const std::string& text, int lb, int le, int rb, int re) {
  while (lb < le) {
    if (text[lb++] != text[rb++]) {
      return false;
    }
  }
  return true;
}

bool CheckEquality(const std::string& text, const std::vector<int64_t>& prefix,
                   const std::vector<int64_t>& powers, int lb, int le, int rb,
                   int re) {
  if (re - rb != le - lb) {
    return false;
  }
  if (GetHash(prefix, powers, ToInt(text[lb]), lb, le) !=
      GetHash(prefix, powers, ToInt(text[rb]), rb, re)) {
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
