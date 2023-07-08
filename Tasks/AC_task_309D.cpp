#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
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

std::vector<int64_t> BFS(int root, const Graph& g) {
  std::vector<int8_t> lookup(g.size());
  std::queue<int> buff;
  buff.push(root);
  lookup[root] = 1;

  std::vector<int64_t> distances(g.size());
  while (!buff.empty()) {
    int curr = buff.front();
    buff.pop();
    for (const auto& el : g[curr]) {
      if (!lookup[el]) {
        lookup[el] = 1;
        buff.push(el);
        distances[el] = distances[curr] + 1;
      }
    }
  }
  return distances;
}

void Solution(std::istream& input) {
  int n1, n2, m;
  input >> n1 >> n2 >> m;

  Graph g(n1 + n2);
  while (m--) {
    int a, b;
    input >> a >> b;
    --a;
    --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  std::vector<int64_t> left = BFS(0, g);
  std::vector<int64_t> right = BFS(g.size() - 1, g);

  int64_t l_max = *std::max_element(left.begin(), left.end());
  int64_t r_max = *std::max_element(right.begin(), right.end());

  std::cout << l_max + r_max + 1 << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
