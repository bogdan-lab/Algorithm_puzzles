#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

int CalcOperations(const std::string& source, const std::string& target);
int GetCharIndex(char ch);
std::vector<std::vector<int>> BuildCharToPos(const std::string& source);

void Solution(std::istream& input = std::cin);
void RunTests();

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
    std::string source;
    std::string target;
    input >> source >> target;
    std::cout << CalcOperations(source, target) << '\n';
  }
}

int CalcOperations(const std::string& source, const std::string& target) {
  std::vector<std::vector<int>> char_to_pos = BuildCharToPos(source);
  int result = 0;
  int curr_pos = std::numeric_limits<int>::min();
  int index = 0;
  while (index < target.size()) {
    int ch_index = GetCharIndex(target[index]);
    if (char_to_pos[ch_index].empty()) return -1;
    auto it = std::upper_bound(char_to_pos[ch_index].begin(),
                               char_to_pos[ch_index].end(), curr_pos);
    if (it == char_to_pos[ch_index].end()) {
      // start new substring
      result++;
      curr_pos = std::numeric_limits<int>::min();
    } else {
      curr_pos = *it;
      ++index;
    }
  }
  return result + 1;
}

int GetCharIndex(char ch) {
  return static_cast<int>(ch) - static_cast<int>('a');
}

std::vector<std::vector<int>> BuildCharToPos(const std::string& source) {
  std::vector<std::vector<int>> result(GetCharIndex('z') + 1);
  for (int i = 0; i < source.size(); ++i) {
    result[GetCharIndex(source[i])].push_back(i);
  }
  return result;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
aabce
ace
abacaba
aax
ty
yyt
)";
    Solution(ss);
    std::cout << "expected = 1; -1; 3\n";
  }
}
