#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int> BuildPrefixArr(const std::string& word);

std::pair<int, int> FindSubString(const std::vector<std::string>& words,
                                  const std::vector<std::vector<int>>& prefix,
                                  int check_size);

bool FindIn(const std::string& lhs_s, int begin, int end,
            const std::string& rhs_s, const std::vector<int>& rhs_p);

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

  std::vector<std::vector<int>> prefix;
  prefix.reserve(n);
  for (const auto& el : words) {
    prefix.push_back(BuildPrefixArr(el));
  }

  int l = 0;
  int r = words.front().size() + 1;
  while (r - l > 1) {
    int mid = (r + l) / 2;
    std::pair<int, int> substr = FindSubString(words, prefix, mid);
    if (substr.first != -1 && substr.second != -1) {
      l = mid;
    } else {
      r = mid;
    }
  }
  auto substr = FindSubString(words, prefix, l);

  for (int i = substr.first; i < substr.second; ++i) {
    std::cout << words[0][i];
  }
  std::cout << '\n';
}

std::vector<int> BuildPrefixArr(const std::string& word) {
  std::vector<int> res(word.size());
  for (int i = 1; i < word.size(); ++i) {
    int j = res[i - 1];
    while (j > 0 && word[i] != word[j]) {
      j = res[j - 1];
    }
    if (word[i] == word[j]) ++j;
    res[i] = j;
  }
  return res;
}

std::pair<int, int> FindSubString(const std::vector<std::string>& words,
                                  const std::vector<std::vector<int>>& prefix,
                                  int check_size) {
  int begin = 0;
  int end = check_size;
  while (end <= words[0].size()) {
    int count = 1;
    for (int i = 1; i < words.size(); ++i) {
      if (FindIn(words[0], begin, end, words[i], prefix[i])) {
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

bool FindIn(const std::string& lhs_s, int begin, int end,
            const std::string& rhs_s, const std::vector<int>& rhs_p) {
  int match_num = 0;
  int len = end - begin;
  for (int i = 0; i < rhs_s.size(); ++i) {
    while (match_num > 0 && lhs_s[begin + match_num] != rhs_s[i]) {
      match_num = rhs_p[match_num - 1];
    }
    if (lhs_s[begin + match_num] == rhs_s[i]) {
      ++match_num;
    }
    if (match_num == len) {
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
