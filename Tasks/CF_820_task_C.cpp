#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
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

int64_t ToNum(char c) {
  return static_cast<int64_t>(c) - static_cast<int64_t>('a');
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  std::string buff;
  while (t--) {
    input >> buff;

    std::vector<std::vector<int>> data(ToNum('z') + 1);
    for (int i = 0; i < buff.size(); ++i) {
      data[ToNum(buff[i])].push_back(i);
    }

    int64_t cost = 0;
    int64_t i = ToNum(buff.front());
    std::vector<int> pos;
    pos.push_back(i);

    if (i <= ToNum(buff.back())) {
      while (i < ToNum(buff.back())) {
        int64_t next = i + 1;
        while (next < ToNum(buff.back()) && data[next].empty()) {
          ++next;
        }
        cost += next - i;
        i = next;
        pos.push_back(i);
      }
    } else {
      while (i > ToNum(buff.back())) {
        int64_t next = i - 1;
        while (next > ToNum(buff.back()) && data[next].empty()) {
          --next;
        }
        cost += i - next;
        i = next;
        pos.push_back(i);
      }
    }

    std::vector<int> res;
    for (const auto& p : pos) {
      for (const auto& el : data[p]) {
        res.push_back(el);
      }
    }

    std::cout << cost << ' ' << res.size() << '\n';
    for (const auto& el : res) {
      std::cout << el + 1 << ' ';
    }
    std::cout << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
logic
codeforces
bca
aaaaaaaaaaa
adbaadabad
to
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
