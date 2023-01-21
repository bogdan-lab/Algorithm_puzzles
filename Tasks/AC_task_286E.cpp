#include <iostream>
#include <queue>
#include <sstream>
#include <string>
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

std::vector<int> GetLevels(const std::vector<std::vector<int>>& graph,
                           int start, int end) {
  std::vector<int> lookup(graph.size());
  std::queue<int> buff;
  buff.push(start);
  lookup[start] = 1;
  std::vector<int> levels(graph.size());
  while (!buff.empty()) {
    int top = buff.front();
    buff.pop();
    for (int i : graph[top]) {
      if (lookup[i]) continue;
      lookup[i] = 1;
      levels[i] = levels[top] + 1;
      buff.push(i);
    }
    if (top == end) break;
  }
  return levels;
}

int64_t DFS(const std::vector<std::vector<int>>& graph, int id, int end,
            int depth, std::vector<int>& lookup,
            const std::vector<int64_t>& prices,
            const std::vector<int>& levels) {
  if (depth > levels[end]) return 0;
  if (lookup[id]) return 0;

  lookup[id] = 1;
  int64_t max_price = 0;
  if (depth == levels[end] && id == end) {
    max_price = prices[id];
  } else if (depth < levels[end]) {
    for (const auto& i : graph[id]) {
      if (levels[i] <= levels[id]) continue;
      max_price = std::max(max_price, prices[id] + DFS(graph, i, end, depth + 1,
                                                       lookup, prices, levels));
    }
  }

  lookup[id] = 0;
  return max_price;
}

int64_t GetMaxPrice(const std::vector<std::vector<int>>& graph, int start,
                    int end, const std::vector<int64_t>& prices,
                    const std::vector<int>& levels) {
  std::vector<int> lookup(graph.size());
  return DFS(graph, start, end, 0, lookup, prices, levels);
}

void Solution(std::istream& input) {
  int n;
  input >> n;

  std::vector<int64_t> prices(n);
  for (auto& el : prices) {
    input >> el;
  }

  std::vector<std::vector<int>> graph(n);

  std::string buff;
  for (int i = 0; i < n; ++i) {
    input >> buff;
    for (int j = 0; j < buff.size(); ++j) {
      if (buff[j] == 'Y') {
        graph[i].push_back(j);
      }
    }
  }

  int q;
  input >> q;
  while (q--) {
    int start, end;
    input >> start >> end;
    --start;
    --end;
    std::vector<int> levels = GetLevels(graph, start, end);
    int64_t max_price = GetMaxPrice(graph, start, end, prices, levels);
    if (max_price) {
      std::cout << levels[end] << ' ' << max_price << '\n';
    } else {
      std::cout << "Impossible\n";
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
30 50 70 20 60
NYYNN
NNYNN
NNNYY
YNNNN
YNNNN
3
1 3
3 1
4 5
)";
    Solution(ss);
    std::cout << "expected = 1 100; 2 160; 3 180\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
100 100
NN
NN
1
1 2
)";
    Solution(ss);
    std::cout << "expected = Impossible\n";
  }
}
