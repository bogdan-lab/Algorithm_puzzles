#ifndef GLOBAL_H
#define GLOBAL_H

#include <algorithm>
#include <functional>
#include <limits>
#include <optional>
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

struct Node {
  ID id = kBadId;
  Node* parent = nullptr;
  Node* son = nullptr;
  double son_weight = kBadWeight;
};

//=======================PRIMA SECTION===========================

class PrimaPriorityQueue {
 public:
  struct HeapElement {
    ID id = kBadId;
    const double* weight_ptr = nullptr;

    HeapElement(ID gid, const double* dbl_ptr) : id(gid), weight_ptr(dbl_ptr) {}
  };

 private:
  enum class PresenceFlag { INSIDE, NOT_INSIDE };

  std::vector<HeapElement> heap_;  // no meaning in index
  std::vector<size_t> pos_;        // index -> key ID, value -> index in heap_
  std::vector<double> vals_;       // index -> key ID
  std::vector<PresenceFlag> presence_;  // index -> key ID

  void MinHeapify(size_t idx) {
    std::optional<size_t> lidx = Left(idx);
    std::optional<size_t> ridx = Right(idx);
    size_t min_idx = idx;
    if (lidx && *heap_[min_idx].weight_ptr < *heap_[*lidx].weight_ptr) {
      min_idx = *lidx;
    }
    if (ridx && *heap_[min_idx].weight_ptr < *heap_[*ridx].weight_ptr) {
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
    return lidx >= heap_.size() ? std::nullopt : lidx;
  }

  std::optional<size_t> Right(size_t idx) {
    size_t ridx = 2 * (idx + 1);
    return ridx >= heap_.size() ? std::nullopt : ridx;
  }

  std::optional<size_t> Parent(size_t idx) {
    int pidx = (idx + 1) / 2 - 1;
    return pidx < 0 ? std::nullopt : pidx;
  }

 public:
  PrimaPriorityQueue(std::vector<double> weights) : vals_(std::move(weights)) {
    heap_.reserve(vals_.size());
    pos_.reserve(vals_.size());
    for (ID i = 0; i < weights.size(); ++i) {
      heap_.emplace_back(i, &weights[i]);
      pos_.push_back(i);
    }
    BuildHeap();
    presence_ = std::vector<PresenceFlag>{heap_.size(), PresenceFlag::INSIDE};
  }

  void Update(ID key, double new_value) {
    if (IsInQueue(key)) {
      vals_[key] = new_value;
      size_t idx = pos_[key];
      std::optional<size_t> pidx = Parent(idx);
      while (pidx && *heap_[idx].weight_ptr < *heap_[*pidx].weight_ptr) {
        std::swap(heap_[idx], heap_[*pidx]);
        std::swap(pos_[heap_[idx].id], pos[heap_[*pidx].id]);
        idx = pidx;
        pidx = Parent(idx);
      }
    }
  }

  HeapElement ExtractMin() {
    std::swap(heap_.front(), heap_.back());
    HeapElement res = heap_.back();
    heap_.pop_back();
    MinHeapify(0);
    presence_[res.id] = PresenceFlag::NOT_INSIDE;
    return res;
  }

  bool IsInQueue(ID id) const { return presence_[id] == PresenceFlag::INSIDE; }

  bool IsEmpty() const { return heap_.empty(); }
};

Node* GetSpanningTreePrima(const Graph& g, ID root_id);
//===============================================================
#endif  // GLOBAL_H
