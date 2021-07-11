#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <optional>
#include <sstream>
#include <unordered_set>
#include <utility>
#include <vector>

using ID = int;

constexpr ID kBadId = -1;
constexpr double kBadWeight = std::numeric_limits<double>::quiet_NaN();

struct Edge {
  ID lhs = kBadId;
  ID rhs = kBadId;
  double weight = kBadWeight;

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

ID ConvertCharToId(char ch) {
  return static_cast<int>(ch) - static_cast<int>('a');
}

char ConvertIdToChar(ID id) {
  return static_cast<char>(static_cast<int>('a') + id);
}

Graph ReadGraph(std::istream& input) {
  int n;
  input >> n;
  Graph g;
  g.edges.reserve(n);
  while (n--) {
    Edge curr_edge;
    char ch_lhs, ch_rhs;
    input >> ch_lhs >> ch_rhs >> curr_edge.weight;
    curr_edge.lhs = ConvertCharToId(ch_lhs);
    curr_edge.rhs = ConvertCharToId(ch_rhs);
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

struct Node {
  ID id = kBadId;
  ID parent = kBadId;
  double parent_weight = kBadWeight;
};

using Tree = std::vector<Node>;

inline std::ostream& operator<<(std::ostream& out, const Tree& tree) {
  for (const auto& el : tree) {
    if (el.parent == kBadId) {
      out << ConvertIdToChar(el.id) << " - ROOT\n";
    } else {
      out << ConvertIdToChar(el.id) << '-' << ConvertIdToChar(el.parent)
          << " : " << el.parent_weight << '\n';
    }
  }
  return out;
}

//=======================PRIMA SECTION===========================

class PrimaPriorityQueue {
 public:
  struct HeapElement {
    ID id = kBadId;
    double weight = kBadWeight;

    HeapElement(ID gid, double dbl) : id(gid), weight(dbl) {}
  };

 private:
  enum class PresenceFlag { INSIDE, NOT_INSIDE };

  std::vector<HeapElement> heap_;  // no meaning in index
  std::vector<size_t> pos_;        // index -> key ID, value -> index in heap_
  std::vector<PresenceFlag> presence_;  // index -> key ID

  void MinHeapify(size_t idx) {
    std::optional<size_t> lidx = Left(idx);
    std::optional<size_t> ridx = Right(idx);
    size_t min_idx = idx;
    if (lidx && heap_[min_idx].weight > heap_[*lidx].weight) {
      min_idx = *lidx;
    }
    if (ridx && heap_[min_idx].weight > heap_[*ridx].weight) {
      min_idx = *ridx;
    }
    if (min_idx != idx) {
      std::swap(heap_[idx], heap_[min_idx]);
      std::swap(pos_[heap_[idx].id], pos_[heap_[min_idx].id]);
      MinHeapify(min_idx);
    }
  }

  void BuildHeap() {
    for (int i = heap_.size() / 2; i >= 0; --i) {
      MinHeapify(i);
    }
  }

  std::optional<size_t> Left(size_t idx) {
    size_t lidx = 2 * idx + 1;
    return lidx >= heap_.size() ? std::nullopt : std::optional<size_t>(lidx);
  }

  std::optional<size_t> Right(size_t idx) {
    size_t ridx = 2 * (idx + 1);
    return ridx >= heap_.size() ? std::nullopt : std::optional<size_t>(ridx);
  }

  std::optional<size_t> Parent(size_t idx) {
    int pidx = (idx + 1) / 2 - 1;
    return pidx < 0 ? std::nullopt : std::optional<size_t>(pidx);
  }

 public:
  PrimaPriorityQueue(const std::vector<double>& weights) {
    heap_.reserve(weights.size());
    for (ID i = 0; i < weights.size(); ++i) {
      heap_.emplace_back(i, weights[i]);
      pos_.push_back(i);
    }
    BuildHeap();
    presence_ = std::vector<PresenceFlag>{heap_.size(), PresenceFlag::INSIDE};
  }

  void Update(ID key, double new_value) {
    if (IsInQueue(key)) {
      size_t idx = pos_[key];
      heap_[idx].weight = new_value;
      std::optional<size_t> pidx = Parent(idx);
      while (pidx && heap_[idx].weight < heap_[*pidx].weight) {
        std::swap(heap_[idx], heap_[*pidx]);
        std::swap(pos_[heap_[idx].id], pos_[heap_[*pidx].id]);
        idx = *pidx;
        pidx = Parent(idx);
      }
    }
  }

  HeapElement ExtractMin() {
    std::swap(heap_.front(), heap_.back());
    std::swap(pos_[heap_.front().id], pos_[heap_.back().id]);
    HeapElement res = heap_.back();
    heap_.pop_back();
    MinHeapify(0);
    presence_[res.id] = PresenceFlag::NOT_INSIDE;
    return res;
  }

  const HeapElement& GetHE(ID key) const { return heap_[pos_[key]]; }

  bool IsInQueue(ID id) const { return presence_[id] == PresenceFlag::INSIDE; }

  bool IsEmpty() const { return heap_.empty(); }
};

Tree GetSpanningTreePrima(const Graph& g, ID root_id) {
  std::vector<double> weights(g.link_repr.size(),
                              std::numeric_limits<double>::max());
  weights[root_id] = 0;
  PrimaPriorityQueue pq{weights};
  Tree tree{g.link_repr.size(), Node{}};
  for (ID i = 0; i < tree.size(); ++i) {
    tree[i].id = i;
  }
  while (!pq.IsEmpty()) {
    auto curr_el = pq.ExtractMin();
    for (const auto& edge : g.link_repr[curr_el.id]) {
      if (pq.IsInQueue(edge.rhs) && edge.weight < pq.GetHE(edge.rhs).weight) {
        pq.Update(edge.rhs, edge.weight);
        tree[edge.rhs].parent = curr_el.id;
        tree[edge.rhs].parent_weight = edge.weight;
      }
    }
  }
  return tree;
}
//===============================================================

int main() {
  std::stringstream ss;
  ss << R"(14
a b 4
a h 8
b c 8
b h 11
c d 7
c i 2
c f 4
d e 9
d f 14
e f 10
i g 6
i h 7
g h 1
g f 2)";
  // min weight sum = 4+8+7+9+2+4+1+2 = 37
  Graph g = ReadGraph(ss);
  std::vector<double> tree_sum(g.link_repr.size(), 0.0);
  for (ID i = 0; i < tree_sum.size(); ++i) {
    Tree prim_tree = GetSpanningTreePrima(g, i);
    for (const auto& el : prim_tree) {
      if (!std::isnan(el.parent_weight)) {
        tree_sum[i] += el.parent_weight;
      }
    }
  }

  for (const auto& el : tree_sum) {
    std::cout << el << " ; ";
  }
  std::cout << '\n';
  return 0;
}
