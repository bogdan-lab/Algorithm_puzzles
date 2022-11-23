#include <algorithm>
#include <cassert>
#include <iterator>
#include <queue>
#include <string>
#include <utility>
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
  for (int i = 0; i < data.size(); ++i) {
    if (ci != i && GetDiffCount(data[ci], data[i]) == 1) {
      graph[ci].push_back(i);
      BuildGraph(data, i, graph);
    }
  }
}

std::vector<int> BFS(const std::vector<std::string>& data, int root,
                     const std::vector<std::vector<int>>& graph) {
  std::vector<int> parents(data.size(), -1);
  std::vector<int8_t> lookup(data.size());
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

int GetMinPathLength(const std::vector<int>& parents, int i) {
  int count = 0;
  while (i >= 0) {
    ++count;
    i = parents[i];
  }
  return count;
}

void DFS(const std::vector<std::vector<int>>& graph, int cid, int eid,
         std::vector<int>& path, int min_len, std::vector<uint8_t>& lookup,
         std::vector<std::vector<int>>& all_pathes) {
  if (lookup[cid]) return;
  lookup[cid] = 1;
  path.push_back(cid);
  if (path.size() < min_len) {
    for (const auto& id : graph[cid]) {
      DFS(graph, id, eid, path, min_len, lookup, all_pathes);
    }
  } else if (path.size() == min_len && cid == eid) {
    all_pathes.push_back(path);
  }
  // restore before going back up
  lookup[cid] = 0;
  path.pop_back();
}

std::vector<std::string> TranslatePath(const std::vector<std::string>& data,
                                       const std::vector<int>& p) {
  std::vector<std::string> res;
  res.reserve(p.size());
  std::transform(p.begin(), p.end(), std::back_inserter(res),
                 [&data](int id) { return data[id]; });
  return res;
}

std::vector<std::vector<std::string>> GetPathesWithLength(
    const std::vector<std::string>& data,
    const std::vector<std::vector<int>>& graph, int bid, int eid, int min_len) {
  std::vector<uint8_t> lookup(data.size());
  std::vector<std::vector<int>> all_pathes;
  std::vector<int> path;
  path.reserve(min_len + 1);
  DFS(graph, bid, eid, path, min_len, lookup, all_pathes);

  std::vector<std::vector<std::string>> res;
  res.reserve(all_pathes.size());
  std::transform(
      all_pathes.begin(), all_pathes.end(), std::back_inserter(res),
      [&data](const std::vector<int>& p) { return TranslatePath(data, p); });
  return res;
}

class Solution {
 public:
  std::vector<std::vector<std::string>> findLadders(
      std::string beginWord, std::string endWord,
      std::vector<std::string>& wordList) {
    int eid =
        std::find(wordList.begin(), wordList.end(), endWord) - wordList.begin();
    if (eid == wordList.size()) return {};
    int bid = std::find(wordList.begin(), wordList.end(), beginWord) -
              wordList.begin();
    if (bid == wordList.size()) {
      wordList.push_back(beginWord);
      bid = wordList.size() - 1;
    }

    std::vector<std::vector<int>> graph(wordList.size());
    BuildGraph(wordList, bid, graph);
    std::vector<int> parents = BFS(wordList, bid, graph);
    if (parents[eid] == -1) return {};
    int min_path_len = GetMinPathLength(parents, eid);

    return GetPathesWithLength(wordList, graph, bid, eid, min_path_len);
  }
};

int main() {
  std::string beginWord = "hot";
  std::string endWord = "dog";
  std::vector<std::string> wordList = {"hot", "dog"};

  Solution s;
  auto result = s.findLadders(beginWord, endWord, wordList);
  return 0;
}
