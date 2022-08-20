#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct Edge {
  int start = 0;
  int end = 0;
  int64_t weight = 0;
};

struct Node {
  explicit Node(int gid) : id(gid), leader(gid), rank(1) {}

  int id = 0;
  int leader = 0;
  int rank = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();

int FindLeader(std::vector<Node>& data, int id);
void Union(std::vector<Node>& data, int lid, int rid);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int vertex_num, edge_num;
  input >> vertex_num >> edge_num;
  std::vector<Node> vertexes;
  vertexes.reserve(vertex_num);
  for (int i = 0; i < vertex_num; ++i) {
    vertexes.push_back(Node(i));
  }

  std::vector<Edge> edges;
  edges.reserve(edge_num);
  while (edge_num--) {
    int l, r;
    int64_t w;
    input >> l >> r >> w;
    edges.push_back({--l, --r, w});
  }

  std::sort(edges.begin(), edges.end(), [](const Edge& lhs, const Edge& rhs) {
    return lhs.weight < rhs.weight;
  });
  int64_t sum = 0;
  for (const auto e : edges) {
    if (FindLeader(vertexes, e.start) != FindLeader(vertexes, e.end)) {
      sum += e.weight;
      Union(vertexes, e.start, e.end);
    }
  }
  std::cout << sum << '\n';
}

void Union(std::vector<Node>& data, int lid, int rid) {
  int lhs_leader = FindLeader(data, lid);
  int rhs_leader = FindLeader(data, rid);
  if (lhs_leader == rhs_leader) return;
  if (data[rhs_leader].rank < data[lhs_leader].rank) {
    data[lhs_leader].leader = data[rhs_leader].leader;
    data[rhs_leader].rank =
        std::max(data[rhs_leader].rank, data[lhs_leader].rank + 1);
  } else {
    data[rhs_leader].leader = data[lhs_leader].leader;
    data[lhs_leader].rank =
        std::max(data[lhs_leader].rank, data[rhs_leader].rank + 1);
  }
}

int FindLeader(std::vector<Node>& data, int id) {
  if (id == data[id].leader) return id;
  data[id].leader = FindLeader(data, data[id].leader);
  return data[id].leader;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4 4
1 2 1
2 3 2
3 4 5
4 1 4
)";
    Solution(ss);
    std::cout << "expected = 7\n";
  }
}
