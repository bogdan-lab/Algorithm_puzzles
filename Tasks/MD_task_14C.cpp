#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int> GetEntrances(const std::string& sub, const std::string& text);
std::vector<int> GetPrefix(const std::string& sub);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::string sub, text;
  input >> sub >> text;
  std::vector<int> entrances = GetEntrances(sub, text);
  std::cout << entrances.size() << '\n';
  for (int e : entrances) {
    std::cout << e + 1 << ' ';
  }
  std::cout << '\n';
}

std::vector<int> GetPrefix(const std::string& sub) {
  std::vector<int> prefix(sub.size());
  for (int i = 1; i < sub.size(); ++i) {
    int j = prefix[i - 1];
    while (j > 0 && sub[i] != sub[j]) {
      j = prefix[j - 1];
    }
    if (sub[i] == sub[j]) ++j;
    prefix[i] = j;
  }
  return prefix;
}

std::vector<int> GetEntrances(const std::string& sub, const std::string& text) {
  std::vector<int> result;
  std::vector<int> prefix = GetPrefix(sub);
  int match_num = 0;
  for (int i = 0; i < text.size(); ++i) {
    while (match_num > 0 && sub[match_num] != text[i]) {
      match_num = prefix[match_num - 1];
    }
    if (sub[match_num] == text[i]) {
      ++match_num;
    }
    if (match_num == sub.size()) {
      result.push_back(i - sub.size() + 1);
      match_num = prefix[match_num - 1];
    }
  }
  return result;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(aba
abaCaba
)";
    Solution(ss);
    std::cout << "expected = 2; 1 5\n";
  }
}
