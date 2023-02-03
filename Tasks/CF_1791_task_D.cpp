#include <algorithm>
#include <iostream>
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

int ToInt(char c) { return static_cast<int>(c) - static_cast<int>('a'); }

void SolveOne(std::istream& input) {
  int n;
  std::string data;
  input >> n >> data;

  int count = 0;
  std::vector<int> buff(ToInt('z') + 1);
  std::vector<int> prefix(data.size());  // inclusive!
  for (int i = 0; i < data.size(); ++i) {
    int val = ToInt(data[i]);
    if (!buff[val]) {
      ++buff[val];
      ++count;
    }
    prefix[i] = count;
  }

  count = 0;
  buff = std::vector<int>(ToInt('z') + 1);
  std::vector<int> suffix(data.size());  // inclusive
  for (int i = data.size() - 1; i >= 0; --i) {
    int val = ToInt(data[i]);
    if (!buff[val]) {
      ++buff[val];
      ++count;
    }
    suffix[i] = count;
  }

  int max = 0;
  for (int i = 1; i < data.size(); ++i) {
    max = std::max(max, prefix[i - 1] + suffix[i]);
  }
  std::cout << max << '\n';
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
