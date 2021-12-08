#include <algorithm>
#include <iostream>
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

std::string GetMinMax(const std::string& initial, int k) {
  std::vector<size_t> count(CharToIdx('z') + 1);
  size_t type_num = 0;
  for (const auto& el : initial) {
    size_t idx = CharToIdx(el);
    if (count[idx] == 0) {
      type_num++;
    }
    count[idx]++;
  }
  if (type_num == 1) {
    return std::string(initial.size() / k, initial.front()) +
           (initial.size() % k ? std::string(1, initial.front()) : "");
  }
  auto it = std::find_if(count.begin(), count.end(),
                         [](const size_t val) { return val != 0; });
  if (type_num == 2 && *it == k) {
    std::string result(1, IdxToChar(it - count.begin()));
    ++it;
    it = std::find_if(it, count.end(), [](size_t val) { return val != 0; });
    char ch = IdxToChar(it - count.begin());
    return result + std::string(*it / k, ch) +
           (*it % k ? std::string(1, ch) : "");
  }
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

