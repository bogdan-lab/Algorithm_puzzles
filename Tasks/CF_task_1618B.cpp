#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
std::string ConstructWord(const std::vector<std::string>& data);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t = 0;
  input >> t;
  std::vector<std::string> data;
  while (t--) {
    int n = 0;
    input >> n;
    n -= 2;
    data.reserve(n);
    while (n--) {
      std::string tmp;
      input >> tmp;
      data.push_back(std::move(tmp));
    }
    std::cout << ConstructWord(data) << '\n';
    data.clear();
  }
}

std::string ConstructWord(const std::vector<std::string>& data) {
  std::string result;
  result.reserve(data.size() + 2);
  bool found_missing = false;
  result += data.front();
  for (size_t i = 1; i < data.size(); ++i) {
    if (data[i - 1][1] != data[i][0]) {
      found_missing = true;
      result += data[i][0];
    }
    result += data[i][1];
  }
  if (!found_missing) {
    result += "a";
  }
  return result;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
7
ab bb ba aa ba
7
ab ba aa ab ba
3
aa
5
bb ab bb
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
