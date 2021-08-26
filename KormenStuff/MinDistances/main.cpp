#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

constexpr double kInf = std::numeric_limits<double>::max();
constexpr size_t kBadId = std::numeric_limits<size_t>::max();

class Graph {
 public:
  struct Edge {
    size_t start;
    size_t end;
    double weight;
  };

  struct Pathes {
    std::vector<size_t> parents;
    std::vector<double> total_length;

    Pathes(size_t node_num)
        : parents(node_num, kBadId), total_length(node_num, kInf) {}

    void Relax(const Edge& edge) {
      if (total_length[edge.end] > total_length[edge.start] + edge.weight) {
        total_length[edge.end] = total_length[edge.start] + edge.weight;
        parents[edge.end] = edge.start;
      }
    }

    void PrintPath(size_t end, std::ostream& out) const {
      std::vector<size_t> p{end};
      size_t parent = parents[end];
      while (parent != kBadId) {
        p.push_back(parent);
        parent = parents[parent];
      }
      out << "Length = " << total_length[end] << " ; "
          << "Route = ";
      for (auto it = p.rbegin(); it != p.rend(); ++it) {
        out << *it << ' ';
      }
      out << '\n';
    }
  };

  Graph(std::istream& input) {
    size_t v_num, e_num;
    input >> v_num >> e_num;
    connections_ = std::vector<std::vector<size_t>>(v_num);
    cashed_pathes_ = std::vector<std::optional<Pathes>>(v_num);
    edges_.reserve(e_num);
    while (e_num--) {
      size_t from, to;
      double w;
      input >> from >> to >> w;
      edges_.push_back({from, to, w});
      connections_[from].push_back(to);
    }
  }

  void PrintPathes(size_t start, std::ostream& out) {
    auto path = DoBelmanFord(start);
    if (!path) {
      out << "Graph contains negative cycles\n";
      return;
    }
    for (size_t nid = 0; nid < path->total_length.size(); ++nid) {
      if (nid != start) path->PrintPath(nid, out);
    }
  }

  const std::optional<Pathes>& DoBelmanFord(size_t start) {
    if (cashed_pathes_[start]) return cashed_pathes_[start];
    Pathes path{connections_.size()};
    path.total_length[start] = 0;
    for (size_t i = 0; i < connections_.size() - 1; ++i) {
      for (const auto& edge : edges_) {
        path.Relax(edge);
      }
    }
    for (const auto& edge : edges_) {
      if (path.total_length[edge.end] >
          path.total_length[edge.start] + edge.weight) {
        return cashed_pathes_[start];
      }
    }
    cashed_pathes_[start] = path;
    return cashed_pathes_[start];
  }

 private:
  std::vector<std::vector<size_t>> connections_;
  std::vector<Edge> edges_;
  std::vector<std::optional<Pathes>> cashed_pathes_;
};

int main() {
  {  // Check on correct graph
    std::stringstream ss;
    ss << R"(5 10
0 1 6.0
0 2 7.0
1 2 8.0
1 3 5.0
3 1 -2.0
1 4 -4.0
2 3 -3.0
2 4 9.0
4 3 7.0
4 0 2.0)";

    Graph g(ss);
    g.PrintPathes(0, std::cout);
  }
  {  // Check on BAD graph
    std::stringstream ss;
    ss << R"(5 10
0 1 6.0
0 2 7.0
1 2 8.0
1 3 1.0
3 1 -2.0
1 4 -4.0
2 3 -3.0
2 4 9.0
4 3 7.0
4 0 2.0)";

    Graph g(ss);
    g.PrintPathes(0, std::cout);
  }
  return 0;
}
