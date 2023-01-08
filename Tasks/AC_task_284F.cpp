#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

constexpr uint64_t A = 1'000'000 + 3;
constexpr uint64_t kMod = 1'000'000'000 + 7;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

uint64_t ToInt(char c) {
  return static_cast<uint64_t>(c) - static_cast<uint64_t>('a');
}

uint64_t GetHash(std::pair<int, int> r, const std::vector<uint64_t>& hashes,
                 const std::vector<uint64_t>& powers) {
  if (r.first == 0) return hashes[r.second - 1];
  if (r.first == r.second) return 0;
  uint64_t lhs = hashes[r.second - 1];
  uint64_t rhs = hashes[r.first - 1] * powers[r.second - r.first];
  rhs %= kMod;
  if (rhs <= lhs) return lhs - rhs;
  return (lhs + kMod) - rhs;
}

bool CompareStrings(const std::string& word, std::pair<int, int> r1,
                    std::pair<int, int> r2) {
  int n = r1.second - r1.first;
  if (n != r2.second - r2.first) return false;
  for (int i = r1.first, j = r2.first; i < n; ++i, ++j) {
    if (word[i] != word[j]) return false;
  }
  return true;
}

bool Compare(const std::string& word, std::pair<int, int> r1,
             std::pair<int, int> r2, const std::vector<uint64_t>& hashes,
             const std::vector<uint64_t>& powers) {
  uint64_t lhs = GetHash(r1, hashes, powers);
  uint64_t rhs = GetHash(r2, hashes, powers);
  if (lhs != rhs) return false;
  return CompareStrings(word, r1, r2);
}

std::pair<int, std::string> Solve(const std::string& word,
                                  const std::vector<uint64_t>& hashes,
                                  const std::vector<uint64_t>& powers) {
  int inner_size = word.size() / 2;
  for (int i = inner_size; i > 0; --i) {
    if (Compare(word, {0, i}, {word.size() - i, word.size()}, hashes, powers) &&
        Compare(word, {i, inner_size}, {inner_size, word.size() - i}, hashes,
                powers)) {
      std::string end = word.substr(inner_size, inner_size - i);
      std::reverse(end.begin(), end.end());
      return {i, word.substr(0, i) + end};
    }
  }
  return {-1, ""};
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::string word;
  input >> word;
  std::reverse(word.begin() + n, word.end());

  std::vector<uint64_t> hashes(word.size());
  hashes[0] = ToInt(word[0]);
  for (int i = 1; i < hashes.size(); ++i) {
    hashes[i] = (hashes[i - 1] * A) % kMod + ToInt(word[i]);
    hashes[i] %= kMod;
  }

  std::vector<uint64_t> powers(word.size());
  powers[0] = 1;
  for (int i = 1; i < powers.size(); ++i) {
    powers[i] = powers[i - 1] * A;
    powers[i] %= kMod;
  }

  std::pair<int, std::string> res = Solve(word, hashes, powers);

  if (res.first == -1) {
    std::cout << "-1\n";
  } else {
    std::cout << res.second << '\n' << res.first << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
abcbac
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
