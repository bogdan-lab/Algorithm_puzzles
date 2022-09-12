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

char FromNum(int num) {
  return static_cast<char>(static_cast<int>('a') + num - 1);
}

int NumFromChar(char c) { return static_cast<int>(c) - static_cast<int>('0'); }

std::vector<std::string> Split(const std::string& data) {
  std::vector<std::string> res;
  res.reserve(data.size());
  int i = 0;
  while (i < data.size()) {
    if (i + 2 < data.size() && data[i + 2] == '0') {
      if (i + 3 < data.size() && data[i + 3] == '0') {
        res.push_back(data.substr(i, 1));
        ++i;
      }
      res.push_back(data.substr(i, 2));
      i += 3;
    } else {
      res.push_back(data.substr(i, 1));
      ++i;
    }
  }

  return res;
}

void Solution(std::istream& input) {
  int q;
  input >> q;
  std::string encoded;
  int n;
  while (q--) {
    input >> n >> encoded;
    std::vector<std::string> splitted = Split(encoded);
    for (const auto& el : splitted) {
      std::cout << FromNum(std::stoi(el));
    }
    std::cout << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(9
6
315045
4
1100
7
1213121
6
120120
18
315045615018035190
7
1111110
7
1111100
5
11111
4
2606
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
