#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <vector>

constexpr int kInfinity = std::numeric_limits<int>::max();

struct VertexEnd {
  int id = 0;
  int weight = 0;
};

class PriorityQueue {
 public:
  PriorityQueue(std::function<bool(int, int)> comp, int vertex_num)
      : compare_(comp), heap_(vertex_num), id_to_pos_(vertex_num) {
    std::iota(heap_.begin(), heap_.end(), 0);
    std::iota(id_to_pos_.begin(), id_to_pos_.end(), 0);
    for (int i = heap_.size() / 2; i >= 0; --i) {
      Heapify(i);
    }
  }

  bool Empty() const { return heap_.empty(); }

  int Top() const { return heap_[0]; }

  void Pop() {
    Swap(0, heap_.size() - 1);
    id_to_pos_[heap_.back()] = kEmptyPos;
    heap_.pop_back();
    if (Empty()) return;
    Heapify(0);
  }

  void DecreaseWeight(int id) {
    if (id_to_pos_[id] == kEmptyPos) return;
    // Need to move element up according to the new value
    int index = id_to_pos_[id];
    int p_index = Parent(index);
    while (p_index >= 0 && compare_(heap_[index], heap_[p_index])) {
      Swap(index, p_index);
      index = p_index;
      p_index = Parent(index);
    }
  }

 private:
  static constexpr int kEmptyPos = -1;
  static int Parent(int index) { return (index + 1) / 2 - 1; }
  static int Left(int index) { return 2 * index + 1; }
  static int Right(int index) { return 2 * index + 2; }

  void Swap(int lhs_index, int rhs_index) {
    using std::swap;
    std::swap(id_to_pos_[heap_[lhs_index]], id_to_pos_[heap_[rhs_index]]);
    std::swap(heap_[lhs_index], heap_[rhs_index]);
  }

  void Heapify(int i) {
    int l = Left(i);
    int r = Right(i);
    int top = i;
    if (l < heap_.size() && compare_(heap_[l], heap_[top])) {
      top = l;
    }
    if (r < heap_.size() && compare_(heap_[r], heap_[top])) {
      top = r;
    }
    if (top != i) {
      Swap(top, i);
      Heapify(top);
    }
  }

  std::vector<int> heap_;
  std::vector<int> id_to_pos_;
  std::function<bool(int, int)> compare_;
};

using Graph = std::vector<std::vector<VertexEnd>>;

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int> Dijkstra(const Graph& graph);

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
  Graph graph(vertex_num);
  while (edge_num--) {
    int start, end, w;
    input >> start >> end >> w;
    --start;
    --end;
    graph[start].push_back({end, w});
    graph[end].push_back({start, w});
  }
  std::vector<int> distances = Dijkstra(graph);
  for (const auto& el : distances) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

std::vector<int> Dijkstra(const Graph& graph) {
  std::vector<int> distances(graph.size(), kInfinity);
  distances[0] = 0;

  auto comparator = [&distances](int lhs_id, int rhs_id) {
    return distances[lhs_id] < distances[rhs_id];
  };

  PriorityQueue pq(comparator, graph.size());

  while (!pq.Empty()) {
    int top_id = pq.Top();
    pq.Pop();
    for (const auto& el : graph[top_id]) {
      distances[el.id] =
          std::min(distances[el.id], distances[top_id] + el.weight);
      pq.DecreaseWeight(el.id);
    }
  }
  return distances;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4 5
1 2 1
1 3 5
2 4 8
3 4 1
2 3 3
)";
    Solution(ss);
    std::cout << "expected = 0 1 4 5\n";
  }
}
