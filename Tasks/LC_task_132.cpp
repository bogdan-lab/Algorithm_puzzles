#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

void CheckRowFor(std::string_view str, int i,
                 std::vector<std::vector<uint8_t>>& res) {
  int j = i;
  res[i][j] = 1;
  bool prev_even = true;
  bool prev_odd = true;
  while (true) {
    --i;
    if (i < 0) break;
    if (str[i] == str[j] && prev_even) {
      res[i][j] = 1;
    } else {
      prev_even = false;
    }
    ++j;
    if (j == res.size()) break;
    if (str[i] == str[j] && prev_odd) {
      res[i][j] = 1;
    } else {
      prev_odd = false;
    }
  }
}

std::vector<std::vector<uint8_t>> BuildMap(std::string_view str) {
  std::vector<std::vector<uint8_t>> res(str.size(),
                                        std::vector<uint8_t>(str.size()));
  for (int i = 0; i < str.size(); ++i) {
    CheckRowFor(str, i, res);
  }
  return res;
}

std::vector<std::vector<int>> BuildGraph(
    const std::vector<std::vector<uint8_t>>& data) {
  std::vector<std::vector<int>> res(data.size() + 1);
  for (int i = 0; i < data.size(); ++i) {
    for (int j = i; j < data[i].size(); ++j) {
      if (data[i][j]) {
        res[i].push_back(j + 1);
      }
    }
  }
  return res;
}

void GetMinSplits(const std::vector<std::vector<uint8_t>>& data, int idx,
                  int curr_count, int& min_count) {
  if (idx >= data.size()) {
    min_count = std::min(min_count, curr_count - 1);
    return;
  }

  if (curr_count - 1 >= min_count) return;

  for (int i = data.size() - 1; i >= idx; --i) {
    if (data[idx][i]) {
      GetMinSplits(data, i + 1, curr_count + 1, min_count);
    }
  }
}

int BFS(const std::vector<std::vector<int>>& data) {
  std::vector<uint8_t> lookup(data.size());
  std::queue<int> buff;
  buff.push(0);
  lookup[0] = 1;
  std::vector<int> dist(data.size());
  while (!buff.empty()) {
    int c = buff.front();
    buff.pop();
    for (const auto& el : data[c]) {
      if (lookup[el]) continue;
      lookup[el] = 1;
      dist[el] = dist[c] + 1;
      buff.push(el);
    }
  }
  return dist.back() - 1;
}

class Solution {
 public:
  int minCut(std::string s) {
    std::vector<std::vector<uint8_t>> data = BuildMap(s);
    std::vector<std::vector<int>> graph = BuildGraph(data);
    return BFS(graph);
  }
};

int main() {
  Solution s;
  int res = s.minCut("ababababababababababababcbabababababababababababa");
  std::cout << res << '\n';
  return 0;
}
