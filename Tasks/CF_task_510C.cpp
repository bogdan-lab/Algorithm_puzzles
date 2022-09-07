#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int ToInt(char c) { return static_cast<int>(c) - static_cast<int>('a'); }
char ToChar(int v) { return static_cast<char>(v + static_cast<int>('a')); }
bool HasCycles(const std::vector<std::vector<int>>& data);
void CycleDFS(const std::vector<std::vector<int>>& data, int id,
              std::vector<int>& lookup, bool& has_cycle);

std::vector<int> TopologicalSort(const std::vector<std::vector<int>>& data);
void TopologicalDFS(const std::vector<std::vector<int>>& data, int id,
                    std::vector<int>& lookup, std::vector<int>& sorted);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<std::string> words(n);
  for (auto& el : words) {
    input >> el;
  }

  std::vector<std::vector<int>> graph(ToInt('z') + 1);
  for (int i = 0; i < words.size() - 1; ++i) {
    size_t len = std::min(words[i].size(), words[i + 1].size());
    int j = 0;
    while (j < len && words[i][j] == words[i + 1][j]) {
      ++j;
    }
    if (j == len) {
      if (words[i].size() > words[i + 1].size()) {
        std::cout << "Impossible\n";
        return;
      } else {
        continue;
      }
    }
    // found connection words[i][j] < words[i+1][j]
    graph[ToInt(words[i + 1][j])].push_back(ToInt(words[i][j]));
  }

  if (HasCycles(graph)) {
    std::cout << "Impossible\n";
    return;
  }

  std::vector<int> sorted = TopologicalSort(graph);
  for (auto el : sorted) {
    std::cout << ToChar(el);
  }
  std::cout << '\n';
}

std::vector<int> TopologicalSort(const std::vector<std::vector<int>>& data) {
  std::vector<int> lookup(data.size());
  std::vector<int> sorted;
  sorted.reserve(data.size());

  for (int i = 0; i < data.size(); ++i) {
    if (lookup[i]) continue;
    TopologicalDFS(data, i, lookup, sorted);
  }

  return sorted;
}

void TopologicalDFS(const std::vector<std::vector<int>>& data, int id,
                    std::vector<int>& lookup, std::vector<int>& sorted) {
  if (lookup[id]) return;
  lookup[id] = 1;
  for (auto next_id : data[id]) {
    TopologicalDFS(data, next_id, lookup, sorted);
  }
  sorted.push_back(id);
}

bool HasCycles(const std::vector<std::vector<int>>& data) {
  std::vector<int> lookup(data.size());
  // 0 - white, 1 - grey, 2 - black
  bool has_cycle = false;
  for (int i = 0; i < data.size(); ++i) {
    if (lookup[i]) continue;
    CycleDFS(data, i, lookup, has_cycle);
    if (has_cycle) break;
  }
  return has_cycle;
}

void CycleDFS(const std::vector<std::vector<int>>& data, int id,
              std::vector<int>& lookup, bool& has_cycle) {
  if (lookup[id] == 1) {
    has_cycle = true;
    return;
  }
  if (lookup[id] == 2) {
    return;
  }

  lookup[id] = 1;
  for (auto next_id : data[id]) {
    CycleDFS(data, next_id, lookup, has_cycle);
  }
  lookup[id] = 2;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
rivest
shamir
adleman
)";
    Solution(ss);
    std::cout << "bcdefghijklmnopqrsatuvwxyz <- expected\n";
  }
  {
    std::stringstream ss;
    ss << R"(10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer
)";
    Solution(ss);
    std::cout << "Impossible <- expected\n";
  }
  {
    std::stringstream ss;
    ss << R"(10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever
)";
    Solution(ss);
    std::cout << "aghjlnopefikdmbcqrstuvwxyz <- expected\n";
  }
  {
    std::stringstream ss;
    ss << R"(7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck
)";
    Solution(ss);
    std::cout << "acbdefhijklmnogpqrstuvwxyz <- expected";
  }
}
