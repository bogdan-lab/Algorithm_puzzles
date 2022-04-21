#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

void Solution(std::istream& input = std::cin);
void RunTests();
bool CheckPainting(std::string_view input);
std::vector<std::string_view> SplitByW(std::string_view input);
bool CheckSplitedPart(std::string_view part);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t = 0;
  input >> t;
  while (t--) {
    int n = 0;
    input >> n;
    std::string target;
    input >> target;
    std::cout << (CheckPainting(target) ? "YES\n" : "NO\n");
  }
}

bool CheckSplitedPart(std::string_view part) {
  if (part.size() == 1) return false;
  return part.front() != part[1] && part.back() != part[part.size() - 1];
}

std::vector<std::string_view> SplitByW(std::string_view input) {
  size_t pos = 0;
  std::vector<std::string_view> result;
  input.remove_prefix(std::min(input.find_first_not_of("W"), input.size()));
  while (!input.empty() && input.back() == 'W') {
    input.remove_suffix(1);
  }
  while (pos < input.size()) {
    size_t next_pos = input.find('W', pos = pos);
    result.push_back(input.substr(pos, next_pos - pos));
    if (next_pos == std::string_view::npos) {
      break;
    }
    while (next_pos < input.size() && input[next_pos] == 'W') {
      next_pos++;
    }
    pos = next_pos;
  }
  return result;
}

bool CheckPainting(std::string_view target) {
  std::vector<std::string_view> splitted = SplitByW(target);
  bool result = true;
  for (const auto& el : splitted) {
    result = result && CheckSplitedPart(el);
  }
  return result;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(12
5
BRBBW
1
B
2
WB
2
RW
3
BRB
3
RBB
7
WWWWWWW
9
RBWBWRRBW
10
BRBRBRBRRB
12
BBBRWWRRRWBR
10
BRBRBRBRBW
5
RBWBW
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
