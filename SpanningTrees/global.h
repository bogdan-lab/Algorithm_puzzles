#ifndef GLOBAL_H
#define GLOBAL_H

#include <algorithm>
#include <functional>
#include <unordered_set>
#include <utility>
#include <vector>

using ID = int;

struct Edge {
  ID lhs;
  ID rhs;
  double weight;

  Edge& Reverse() {
    std::swap(lhs, rhs);
    return *this;
  }
};

struct Graph {
  // sorted by weight vector of unique edges
  std::vector<Edge> edges;
  // linked list representation
  std::vector<std::vector<Edge>> link_repr;
};

inline Graph read_graph(std::istream& input) {
  int n;
  input >> n;
  Graph g;
  g.edges.reserve(n);
  while (n--) {
    Edge curr_edge;
    input >> curr_edge.lhs >> curr_edge.rhs >> curr_edge.weight;
    g.edges.push_back(curr_edge);
    ID max_id = std::max(curr_edge.lhs, curr_edge.rhs);
    if (g.link_repr.size() <= max_id) {
      g.link_repr.resize(max_id + 1);
    }
    g.link_repr[curr_edge.lhs].push_back(curr_edge);
    g.link_repr[curr_edge.rhs].push_back(std::move(curr_edge.Reverse()));
  }
  std::sort(
      g.edges.begin(), g.edges.end(),
      [](const Edge& lhs, const Edge& rhs) { return lhs.weight < rhs.weight; });
  return g;
}

#endif  // GLOBAL_H
