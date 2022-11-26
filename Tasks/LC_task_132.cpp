#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

void CheckRowFor(const std::string& str, int16_t i,
                 std::vector<std::vector<int16_t>>& res) {
  int16_t j = i;
  res[i].push_back(j + 1);
  bool prev_even = true;
  bool prev_odd = true;
  while (true) {
    --i;
    if (i < 0) break;
    if (str[i] == str[j] && prev_even) {
      res[i].push_back(j + 1);
    } else {
      prev_even = false;
    }
    ++j;
    if (j == res.size()) break;
    if (str[i] == str[j] && prev_odd) {
      res[i].push_back(j + 1);
    } else {
      prev_odd = false;
    }
  }
}

std::vector<std::vector<int16_t>> BuildGraph(const std::string& str) {
  std::vector<std::vector<int16_t>> res(str.size() + 1);
  for (int16_t i = 0; i < str.size(); ++i) {
    CheckRowFor(str, i, res);
  }
  return res;
}

int BFS(const std::vector<std::vector<int16_t>>& data) {
  std::vector<uint8_t> lookup(data.size());
  std::queue<int16_t> buff;
  buff.push(0);
  lookup[0] = 1;
  std::vector<int16_t> dist(data.size());
  bool found_end = false;
  while (!buff.empty()) {
    int c = buff.front();
    buff.pop();
    for (const auto& el : data[c]) {
      if (lookup[el]) continue;
      lookup[el] = 1;
      dist[el] = dist[c] + 1;
      buff.push(el);
      found_end = el == data.size() - 1;
    }
    if (found_end) break;
  }
  return dist.back() - 1;
}

class Solution {
 public:
  int minCut(std::string s) { return BFS(BuildGraph(s)); }
};

int main() {
  Solution s;
  int res = s.minCut("ababababababababababababcbabababababababababababa");
  std::cout << res << '\n';
  return 0;
}
