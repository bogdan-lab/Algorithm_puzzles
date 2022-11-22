#include <algorithm>
#include <cassert>
#include <queue>
#include <string>
#include <vector>

int GetDiffCount(const std::string& l, const std::string& r) {
  assert(l.size() == r.size());
  int diff_count = 0;
  for (int i = 0; i < l.size(); ++i) {
    diff_count += (l[i] != r[i]);
  }
  return diff_count;
}

void BuildGraph(const std::vector<std::string>& data, int ci,
                std::vector<std::vector<int>>& graph) {
  assert(graph.size() == data.size());
  if (!graph[ci].empty()) return;
  for (int i = ci - 1; i >= 0; --i) {
    if (GetDiffCount(data[ci], data[i]) == 1) {
      graph[ci].push_back(i);
      BuildGraph(data, i, graph);
    }
  }
}

std::vector<int> BFS(const std::vector<std::string>& data, int root,
                     const std::vector<std::vector<int>>& graph) {
  std::vector<int> parents(data.size());
  std::vector<int8_t> lookup(data.size());
  parents[root] = -1;
  std::queue<int> buff;
  buff.push(root);
  lookup[root] = 1;
  while (!buff.empty()) {
    int c = buff.front();
    for (const auto& el : graph[c]) {
      if (!lookup[el]) {
        lookup[el] = 1;
        buff.push(el);
        parents[el] = c;
      }
    }
    buff.pop();
  }
  return parents;
}

void AggregatePath(const std::vector<std::string>& data, int i,
                   const std::vector<int>& parents,
                   std::vector<std::string>& path) {
  while (i >= 0) {
    path.push_back(data[i]);
    i = parents[i];
  }
}

std::vector<std::vector<std::string>> GetMinPathes(
    const std::vector<std::string>& data, const std::vector<int>& parents,
    const std::string& begin) {
  std::vector<std::vector<std::string>> res;
  for (int i = 0; i < data.size(); ++i) {
    std::vector<std::string> path;
    int dc = GetDiffCount(data[i], begin);
    if (dc > 1) {
      continue;
    } else if (dc == 1) {
      path.push_back(begin);
      AggregatePath(data, i, parents, path);
    } else {
      AggregatePath(data, i, parents, path);
    }
    if (!res.empty() && path.size() > res.back().size()) {
      continue;
    }
    while (!res.empty() && path.size() < res.back().size()) {
      res.pop_back();
    }
    res.push_back(path);
  }
  return res;
}

class Solution {
 public:
  std::vector<std::vector<std::string>> findLadders(
      std::string beginWord, std::string endWord,
      std::vector<std::string>& wordList) {
    auto it = std::find(wordList.begin(), wordList.end(), endWord);
    if (it == wordList.end()) return {};
    wordList.erase(std::next(it), wordList.end());
    if (wordList.empty()) return {};

    std::vector<std::vector<int>> graph(wordList.size());
    BuildGraph(wordList, wordList.size() - 1, graph);

    std::vector<int> parents = BFS(wordList, wordList.size() - 1, graph);
    return GetMinPathes(wordList, parents, beginWord);
  }
};
