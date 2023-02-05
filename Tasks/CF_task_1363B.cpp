#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

struct Node {
  int zeros = 0;
  int ones = 0;
};

void Consume(Node& node, char c) {
  if (c == '1') {
    node.ones += 1;
  } else {
    node.zeros += 1;
  }
}

int CalcMinReplacements(const std::string& data) {
  std::vector<Node> prefix(data.size());  // inclusive!
  Consume(prefix[0], data[0]);

  for (int i = 1; i < data.size(); ++i) {
    prefix[i] = prefix[i - 1];
    Consume(prefix[i], data[i]);
  }

  std::vector<Node> suffix(data.size());  // inclusive!
  Consume(suffix.back(), data.back());
  for (int i = static_cast<int>(data.size()) - 2; i >= 0; --i) {
    suffix[i] = suffix[i + 1];
    Consume(suffix[i], data[i]);
  }

  int count = std::min(suffix[0].zeros, prefix.back().ones);
  for (int i = 1; i < data.size(); ++i) {
    count = std::min(count, suffix[i].zeros + prefix[i - 1].ones);
  }
  return count;
}

void SolveOne(std::istream& input) {
  std::string data;
  input >> data;

  int c01 = CalcMinReplacements(data);
  std::reverse(data.begin(), data.end());
  int c02 = CalcMinReplacements(data);
  std::cout << std::min(c01, c02) << '\n';
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
