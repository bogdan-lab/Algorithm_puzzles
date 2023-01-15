#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
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

int AddWord(std::unordered_map<std::string, int>& mp, const std::string& word,
            int curr_i) {
  auto it = mp.find(word);
  if (it == mp.end()) {
    mp[word] = curr_i;
    return curr_i + 1;
  }
  return curr_i;
}

bool DFS(const std::vector<std::vector<int>>& g, int id,
         std::vector<int>& lookup, int lvl) {
  if (lookup[id] == lvl) return true;
  if (lookup[id] > 0) return false;
  lookup[id] = lvl;

  bool result = false;
  for (const auto& i : g[id]) {
    result = result || DFS(g, i, lookup, lvl);
  }
  return result;
}

bool HasCycle(const std::vector<std::vector<int>>& g) {
  std::vector<int> lookup(g.size());

  int lvl = 1;
  for (int i = 0; i < g.size(); ++i) {
    if (lookup[i]) continue;
    if (DFS(g, i, lookup, lvl)) return true;
    ++lvl;
  }
  return false;
}

void Solution(std::istream& input) {
  int n;
  input >> n;

  std::unordered_map<std::string, int> counter;
  std::vector<std::pair<std::string, std::string>> data(n);
  int i = 0;
  for (auto& el : data) {
    input >> el.first >> el.second;
    i = AddWord(counter, el.first, i);
    i = AddWord(counter, el.second, i);
  }

  std::vector<std::vector<int>> graph(counter.size());
  for (const auto& el : data) {
    auto from = counter.find(el.first);
    assert(from != counter.end());
    auto to = counter.find(el.second);
    assert(to != counter.end());

    graph[from->second].push_back(to->second);
  }

  if (HasCycle(graph)) {
    std::cout << "No\n";
  } else {
    std::cout << "Yes\n";
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
b m
m d
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
