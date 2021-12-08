#include <algorithm>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
std::string GetMinMax(const std::string& initial, int k);
size_t CharToIdx(char ch);
char IdxToChar(size_t idx);
std::string ConstructSortedString(const std::vector<size_t>& count);
std::string GetNthLetter(const std::vector<size_t>& count, size_t k);

std::optional<std::string> ConstructFromOneLetter(
    const std::vector<size_t>& count, size_t k, size_t str_len);
std::optional<std::string> TryCreateSameStrings(
    const std::vector<size_t>& count, size_t k, size_t str_len);

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
    int len;
    int k;
    input >> len >> k;
    std::string initial;
    input >> initial;
    std::cout << GetMinMax(initial, k) << '\n';
  }
}

size_t CharToIdx(char ch) {
  return static_cast<size_t>(ch) - static_cast<size_t>('a');
}

char IdxToChar(size_t idx) {
  return static_cast<char>(idx + static_cast<size_t>('a'));
}

std::optional<std::string> TryCreateSameStrings(
    const std::vector<size_t>& count, size_t k, size_t str_len) {
  if (str_len % k) return std::nullopt;
  std::string result;
  for (size_t i = 0; i < count.size(); ++i) {
    if (count[i] % k) {
      return std::nullopt;
    } else {
      result += std::string(count[i] / k, IdxToChar(i));
    }
  }
  return result;
}

std::optional<std::string> ConstructFromOneLetter(
    const std::vector<size_t>& count, size_t k, size_t str_len) {
  auto it = std::find_if(count.begin(), count.end(),
                         [](const size_t val) { return val != 0; });
  if (*it != str_len) return std::nullopt;
  char ch = IdxToChar(it - count.begin());
  return std::string(str_len / k, ch) + (str_len % k ? std::string(1, ch) : "");
}

std::string GetMinMax(const std::string& initial, int k) {
  std::vector<size_t> count(CharToIdx('z') + 1);
  for (const auto& el : initial) {
    count[CharToIdx(el)]++;
  }

  auto copied_str = TryCreateSameStrings(count, k, initial.size());
  if (copied_str) {
    return *copied_str;
  }
  auto one_letter_string = ConstructFromOneLetter(count, k, initial.size());
  if (one_letter_string) {
    return *one_letter_string;
  }
  auto it = std::find_if(count.begin(), count.end(),
                         [](const size_t val) { return val != 0; });
  if (*it >= k) {
    *it -= k - 1;
    return ConstructSortedString(count);
  } else {
    return GetNthLetter(count, k);
  }
}

std::string GetNthLetter(const std::vector<size_t>& count, size_t k) {
  size_t idx = 0;
  while (true) {
    if (k > count[idx]) {
      k -= count[idx++];
    } else {
      break;
    }
  }
  return std::string(1, IdxToChar(idx));
}

std::string ConstructSortedString(const std::vector<size_t>& count) {
  std::string result;
  for (std::size_t i = 0; i < count.size(); ++i) {
    if (count[i] > 0) {
      result += std::string(count[i], IdxToChar(i));
    }
  }
  return result;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
4 2
baba
5 2
baacb
5 3
baacb
5 3
aaaaa
6 4
aaxxzz
7 1
phoenix
)";
    Solution(ss);
    std::cout << "expected = ab; abbc; b; aa; x; ehinopx\n";
  }
}

