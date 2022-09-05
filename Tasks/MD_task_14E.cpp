#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

constexpr int64_t kPolCoef = 29;
constexpr int64_t kModCoef = 1000'000'007;

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int64_t> MakePrefix(const std::string& str);
std::vector<int64_t> MakePowers(int num);
int64_t ToInt(char c) {
  return static_cast<int>(c) - static_cast<int>('a') + 1;
}

std::pair<int, int> FindSubString(
    const std::vector<std::string>& words,
    const std::vector<std::vector<int64_t>>& prefix,
    const std::vector<int64_t>& powers, int check_size);

bool FindIn(const std::string& lhs_s, int begin, int end,
            const std::string& rhs_s, const std::vector<int64_t>& lhs_p,
            const std::vector<int64_t>& rhs_p,
            const std::vector<int64_t>& powers);
int64_t GetHash(const std::vector<int64_t>& prefix,
                const std::vector<int64_t>& powers, int b, int e);
bool ActualCompare(const std::string& lhs, int bl, int el,
                   const std::string& rhs, int br, int er);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<std::string> words(n);
  for (auto& el : words) {
    input >> el;
  }

  std::sort(words.begin(), words.end(),
            [](const std::string& lhs, const std::string& rhs) {
              return lhs.size() < rhs.size();
            });

  std::vector<std::vector<int64_t>> prefix;
  prefix.reserve(n);
  for (const auto& el : words) {
    prefix.push_back(MakePrefix(el));
  }

  std::vector<int64_t> powers = MakePowers(words.back().size());

  int l = 0;
  int r = words.front().size() + 1;
  while (r - l > 1) {
    int mid = (r + l) / 2;
    std::pair<int, int> substr = FindSubString(words, prefix, powers, mid);
    if (substr.first != -1 && substr.second != -1) {
      l = mid;
    } else {
      r = mid;
    }
  }
  auto substr = FindSubString(words, prefix, powers, l);

  for (int i = substr.first; i < substr.second; ++i) {
    std::cout << words[0][i];
  }
  std::cout << '\n';
}

std::vector<int64_t> MakePrefix(const std::string& str) {
  std::vector<int64_t> res(str.size());
  res[0] = ToInt(str[0]);
  for (int i = 1; i < res.size(); ++i) {
    res[i] = ((kPolCoef * res[i - 1]) % kModCoef + ToInt(str[i])) % kModCoef;
  }
  return res;
}

std::vector<int64_t> MakePowers(int num) {
  std::vector<int64_t> res(num);
  res[0] = 1;
  for (int i = 1; i < res.size(); ++i) {
    res[i] = (res[i - 1] * kPolCoef) % kModCoef;
  }
  return res;
}

std::pair<int, int> FindSubString(
    const std::vector<std::string>& words,
    const std::vector<std::vector<int64_t>>& prefix,
    const std::vector<int64_t>& powers, int check_size) {
  int begin = 0;
  int end = check_size;
  while (end <= words[0].size()) {
    int count = 1;
    for (int i = 1; i < words.size(); ++i) {
      if (FindIn(words[0], begin, end, words[i], prefix[0], prefix[i],
                 powers)) {
        ++count;
      } else {
        break;
      }
    }
    if (count == words.size()) {
      return {begin, end};
    }
    ++begin;
    ++end;
  }
  return {-1, -1};
}

int64_t GetHash(const std::vector<int64_t>& prefix,
                const std::vector<int64_t>& powers, int b, int e) {
  if (b == e) return 0;
  int64_t lhs = b == 0 ? 0 : (prefix[b - 1] * powers[e - b]) % kModCoef;
  int64_t res = prefix[e - 1] - lhs;
  return res < 0 ? res + kModCoef : res;
}

bool ActualCompare(const std::string& lhs, int bl, int el,
                   const std::string& rhs, int br, int er) {
  for (int i = bl, j = br; i < el; ++i, ++j) {
    if (lhs[i] != rhs[j]) return false;
  }
  return true;
}

bool FindIn(const std::string& lhs_s, int begin, int end,
            const std::string& rhs_s, const std::vector<int64_t>& lhs_p,
            const std::vector<int64_t>& rhs_p,
            const std::vector<int64_t>& powers) {
  int64_t lhs_h = GetHash(lhs_p, powers, begin, end);
  int len = end - begin;
  for (int i = 0; i <= rhs_s.size() - len; ++i) {
    int j = i + len;
    int64_t rhs_h = GetHash(rhs_p, powers, i, j);
    if (lhs_h != rhs_h) {
      continue;
    } else if (ActualCompare(lhs_s, begin, end, rhs_s, i, j)) {
      return true;
    }
  }
  return false;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
abacaba
mycabarchive
acabistrue
)";
    Solution(ss);
    std::cout << "expected = cab\n";
  }
}
