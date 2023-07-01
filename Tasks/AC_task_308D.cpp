#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

char GetNextChar(char curr_char) {
  switch (curr_char) {
    case 's':
      return 'n';
    case 'n':
      return 'u';
    case 'u':
      return 'k';
    case 'k':
      return 'e';
    case 'e':
      return 's';
  }
  return '\0';
}

int GetId(int ch, int cw, int w) { return ch * w + cw; }

void CheckConnect(Graph& g, const std::vector<std::string>& grid, int ch,
                  int cw, int nh, int nw) {
  if (nh < 0 || nw < 0) return;
  if (nh >= grid.size() || nw >= grid.front().size()) return;
  char curr = grid[ch][cw];
  char next = GetNextChar(curr);
  if (grid[nh][nw] != next) return;
  int c_id = GetId(ch, cw, grid.front().size());
  int n_id = GetId(nh, nw, grid.front().size());
  g[c_id].push_back(n_id);
}

Graph BuildGraph(const std::vector<std::string>& grid) {
  Graph res(grid.size() * grid.front().size());
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[i].size(); ++j) {
      CheckConnect(res, grid, i, j, i + 1, j);
      CheckConnect(res, grid, i, j, i - 1, j);
      CheckConnect(res, grid, i, j, i, j + 1);
      CheckConnect(res, grid, i, j, i, j - 1);
    }
  }
  return res;
}

void DFS(const Graph& g, int id, std::vector<int8_t>& lookup) {
  if (lookup[id]) return;
  lookup[id] = 1;

  for (const auto& nid : g[id]) {
    DFS(g, nid, lookup);
  }
}

bool DoDFS(const Graph& g) {
  std::vector<int8_t> lookup(g.size());

  DFS(g, 0, lookup);

  return lookup.back() > 0;
}

void Solution(std::istream& input) {
  int h, w;
  input >> h >> w;

  std::vector<std::string> grid(h);
  for (auto& el : grid) {
    input >> el;
  }

  Graph g = BuildGraph(grid);

  if (DoDFS(g)) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
