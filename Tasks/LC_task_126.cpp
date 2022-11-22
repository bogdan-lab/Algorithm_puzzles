#include <algorithm>
#include <cassert>
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

std::vector<std::string> AggregatePath(const std::vector<std::string>& data,
                                       int i, const std::vector<int>& parents) {
  std::vector<std::string> path;
  while (i >= 0) {
    path.push_back(data[i]);
    i = parents[i];
  }
  return path;
}

std::vector<std::vector<std::string>> BuildShortestPathes(
    const std::vector<std::string>& data, const std::vector<int>& parents) {
  std::vector<std::vector<std::string>> pathes;
  pathes.reserve(data.size());
  for (int i = 0; i < data.size(); ++i) {
    pathes.push_back(AggregatePath(data, i, parents));
  }
  return pathes;
}

std::vector<std::vector<int>> RevertGraph(
    const std::vector<std::vector<int>>& graph) {
  std::vector<std::vector<int>> res(graph.size());
  for (int i = 0; i < graph.size(); ++i) {
    for (const auto& id : graph[i]) {
      res[id].push_back(i);
    }
  }
  return res;
}

std::vector<std::string> Merge(const std::vector<std::string>& prefix,
                               const std::vector<std::string>& suffix) {
  std::vector<std::string> res;
  res.reserve(prefix.size() + suffix.size());
  for (const auto& el : prefix) {
    res.push_back(el);
  }
  for (const auto& el : suffix) {
    res.push_back(el);
  }
  return res;
}

bool IsUnique(const std::vector<std::string>& p,
              const std::vector<std::vector<std::string>>& data) {
  for (const auto& el : data) {
    if (p == el) return false;
  }
  return true;
}

void GluePathes(const std::vector<std::vector<int>>& r_graph,
                const std::vector<std::string>& prefix, int id,
                const std::vector<std::vector<std::string>>& suf_path,
                std::vector<std::vector<std::string>>& coll) {
  for (const auto& n_id : r_graph[id]) {
    int new_size = prefix.size() + suf_path[n_id].size();
    if (coll.empty() || coll.back().size() >= new_size) {
      if (!coll.empty() && coll.back().size() > new_size) {
        coll.clear();
      }
      std::vector<std::string> p = Merge(prefix, suf_path[n_id]);
      if (IsUnique(p, coll)) {
        coll.push_back(std::move(p));
      }
    }
    // try deeper branching
    if (!suf_path[n_id].empty()) {
      GluePathes(r_graph, Merge(prefix, {suf_path[n_id].front()}), n_id,
                 suf_path, coll);
    }
  }
}

std::vector<std::vector<std::string>> BuildMinPathes(
    const std::vector<std::string>& data, const std::string& bw,
    const std::vector<std::vector<int>>& r_graph,
    const std::vector<std::vector<std::string>>& suf_path) {
  std::vector<std::vector<std::string>> res;

  for (int i = 0; i < r_graph.size(); ++i) {
    int diff = GetDiffCount(bw, data[i]);
    if (diff > 1) continue;
    std::vector<std::string> cp;
    if (diff == 1) cp.push_back(bw);
    cp.push_back(data[i]);
    GluePathes(r_graph, cp, i, suf_path, res);
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
    std::vector<std::vector<std::string>> shortest_pathes =
        BuildShortestPathes(wordList, parents);

    std::vector<std::vector<int>> reverted = RevertGraph(graph);
    return BuildMinPathes(wordList, beginWord, reverted, shortest_pathes);
  }
};

int main() {
  std::string beginWord = "hit";
  std::string endWord = "cog";
  std::vector<std::string> wordList = {"hot", "dot", "dog",
                                       "lot", "log", "cog"};

  Solution s;
  auto result = s.findLadders(beginWord, endWord, wordList);
  return 0;
}
