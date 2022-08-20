#include <algorithm>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

struct Node {
  explicit Node(int gid) : id(gid), leader(gid), rank(1) {}
  int id = 0;
  int leader = 0;
  int rank = 0;
};

int FindLeader(std::vector<Node>& dsu, int id);
void Join(std::vector<Node>& dsu, int lhs, int rhs);

struct Edge {
  int end = 0;
  int64_t weight = 0;
};

struct ReversedEdge {
  int start = 0;
  int64_t weight = 0;
};

class SortedVector {
 public:
  void Sort() {
    std::sort(data_.begin(), data_.end(),
              [](const ReversedEdge& lhs, const ReversedEdge& rhs) {
                return lhs.weight < rhs.weight;
              });
  }

  void PushBack(ReversedEdge edge) { data_.push_back(edge); }

  bool Empty() const { return pos_ >= data_.size(); }
  ReversedEdge Top() const { return data_[pos_]; }
  void PopFront() { ++pos_; }

 private:
  std::vector<ReversedEdge> data_;
  size_t pos_ = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();

bool CheckIsConnected(const std::vector<std::vector<Edge>>& data);
void DFS(int id, const std::vector<std::vector<Edge>>& data,
         std::vector<int>& lookup);

int64_t GetMSTWeight(std::vector<SortedVector>& graph, std::vector<Node>& dsu);

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
  std::vector<Node> dsu;
  dsu.reserve(vertex_num);
  for (int i = 0; i < vertex_num; ++i) {
    dsu.push_back(Node(i));
  }
  std::vector<std::vector<Edge>> raw_edges(vertex_num);
  std::vector<SortedVector> graph(vertex_num);
  while (edge_num--) {
    int l, r;
    int64_t w;
    input >> l >> r >> w;
    raw_edges[--l].push_back({--r, w});
    graph[r].PushBack({l, w});
  }
  for (auto& el : graph) {
    el.Sort();
  }
  if (!CheckIsConnected(raw_edges)) {
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n" << GetMSTWeight(graph, dsu) << '\n';
}

void Join(std::vector<Node>& dsu, int lhs, int rhs) {
  int lhs_leader = FindLeader(dsu, lhs);
  int rhs_leader = FindLeader(dsu, rhs);
  if (lhs_leader == rhs_leader) return;
  if (dsu[lhs_leader].rank < dsu[rhs_leader].rank) {
    dsu[rhs_leader].rank =
        std::max(dsu[rhs_leader].rank, dsu[lhs_leader].rank + 1);
    dsu[lhs_leader].leader = rhs_leader;
  } else {
    dsu[lhs_leader].rank =
        std::max(dsu[lhs_leader].rank, dsu[rhs_leader].rank + 1);
    dsu[rhs_leader].leader = lhs_leader;
  }
}

int64_t GetMSTWeight(std::vector<SortedVector>& graph, std::vector<Node>& dsu) {
  int64_t result = 0;
  std::vector<int64_t> delta(graph.size());
  std::vector<int> used(graph.size());
  int timer = 0;
  for (int id = 0; id < graph.size(); ++id) {
    if (FindLeader(dsu, 0) == FindLeader(dsu, id)) {
      continue;  // the vertex is already connected to the root
    }
    ++timer;
    std::vector<int> path;
    path.push_back(id);
    while (FindLeader(dsu, path.back()) != FindLeader(dsu, 0)) {
      int curr_id = FindLeader(dsu, path.back());
      used[curr_id] = timer;
      ReversedEdge min_edge = graph[curr_id].Top();
      while (FindLeader(dsu, min_edge.start) == FindLeader(dsu, curr_id)) {
        graph[curr_id].PopFront();
        min_edge = graph[curr_id].Top();
      }
      int next_id = FindLeader(dsu, min_edge.start);
      result += min_edge.weight + delta[curr_id];
      delta[curr_id] -= min_edge.weight + delta[curr_id];
      if (used[next_id] != timer) {
        path.push_back(next_id);
        continue;
      }
      // Here we encountered cycle -> delete it
      while (!path.empty() &&
             FindLeader(dsu, path.back()) != FindLeader(dsu, next_id)) {
        Join(dsu, path.back(), next_id);
        path.pop_back();
      }
    }
    // Connect everything in path with the root
    while (!path.empty()) {
      Join(dsu, path.back(), 0);
      path.pop_back();
    }
  }
  return result;
}

int FindLeader(std::vector<Node>& dsu, int id) {
  if (id == dsu[id].leader) return id;
  dsu[id].leader = FindLeader(dsu, dsu[id].leader);
  return dsu[id].leader;
}

bool CheckIsConnected(const std::vector<std::vector<Edge>>& data) {
  int count = 0;
  std::vector<int> lookup(data.size());
  for (int id = 0; id < data.size(); ++id) {
    if (lookup[id]) continue;
    ++count;
    if (count > 1) return false;
    DFS(0, data, lookup);
  }
  return true;
}

void DFS(int id, const std::vector<std::vector<Edge>>& data,
         std::vector<int>& lookup) {
  if (lookup[id]) return;
  lookup[id] = 1;
  for (const auto& e : data[id]) {
    DFS(e.end, data, lookup);
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2 1
2 1 10
)";
    Solution(ss);
    std::cout << "expected = NO\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 5
1 2 2
1 3 3
1 4 3
2 3 2
2 4 2
)";
    Solution(ss);
    std::cout << "expected = YES; 6\n";
  }
}
