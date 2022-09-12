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
    std::vector<std::pair<char, int>> c_to_p;
    c_to_p.reserve(buff.size());
    for (int i = 0; i < buff.size(); ++i) {
      c_to_p.push_back({buff[i], i});
    }
    std::sort(c_to_p.begin(), c_to_p.end());
    auto begin = std::find_if(c_to_p.begin(), c_to_p.end(),
                              [](const auto& p) { return p.second == 0; });
    auto end = std::find_if(begin, c_to_p.end(), [&](const auto& p) {
      return p.second == buff.size() - 1;
    });
    if (end == c_to_p.end()) {
      std::reverse(c_to_p.begin(), c_to_p.end());
      begin = std::find_if(c_to_p.begin(), c_to_p.end(),
                           [](const auto& p) { return p.second == 0; });
      end = std::find_if(c_to_p.begin(), c_to_p.end(), [&](const auto& p) {
        return p.second == buff.size() - 1;
      });
    }
    ++end;

    int64_t cost = 0;
    auto it = begin;
    while (it != std::prev(end)) {
      auto next = std::next(it);
      cost += std::abs(ToNum(it->first) - ToNum(next->first));
      it = next;
    }
    std::cout << cost << ' ' << (end - begin) << '\n';
    for (auto jt = begin; jt != end; ++jt) {
      std::cout << jt->second + 1 << ' ';
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
