#include <iostream>
#include <sstream>
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

struct Node {
  int v_num = 0;
  int e_num = 0;
};

void DFS(const std::vector<std::vector<int>>& graph, int cid,
         std::vector<int>& lookup, Node& node) {
  if (lookup[cid]) {
    return;
  }
  lookup[cid] = 1;
  ++node.v_num;
  for (const auto& id : graph[cid]) {
    ++node.e_num;
    DFS(graph, id, lookup, node);
  }
}

int CountDeletion(const std::vector<std::vector<int>>& graph) {
  std::vector<int> lookup(graph.size());

  std::vector<Node> trees;
  for (int i = 0; i < graph.size(); ++i) {
    if (lookup[i]) continue;
    Node node;
    DFS(graph, i, lookup, node);
    node.e_num /= 2;
    trees.push_back(node);
  }

  int count = 0;
  for (const auto& el : trees) {
    if (el.e_num > el.v_num - 1) {
      count += el.e_num - el.v_num + 1;
    }
  }
  return count;
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;

  std::vector<std::vector<int>> graph(n);
  while (m--) {
    int a, b;
    input >> a >> b;
    --a;
    --b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  std::cout << CountDeletion(graph) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5 3
1 2
1 3
2 3
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
