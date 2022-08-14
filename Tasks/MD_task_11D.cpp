#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

enum class DistanceState { kValid, kAbsent, kNoMinimum };

struct DistanceValue {
  uint64_t abs_val = std::numeric_limits<uint64_t>::max();
  bool is_positive = true;
  DistanceState state = DistanceState::kAbsent;
};

bool operator==(const DistanceValue& l, const DistanceValue& r) {
  return l.abs_val == r.abs_val && l.is_positive == r.is_positive &&
         l.state == r.state;
}

bool operator!=(const DistanceValue& l, const DistanceValue& r) {
  return !(l == r);
}

struct WeightValue {
  explicit WeightValue(int64_t w) {
    if (w < 0) {
      abs_val = -w;
      is_positive = false;
    } else {
      abs_val = w;
      is_positive = true;
    }
  }
  uint64_t abs_val = 0;
  bool is_positive = true;
};

struct VertexEnd {
  int id = 0;
  WeightValue weight;
};

using Graph = std::vector<std::vector<VertexEnd>>;

DistanceValue Relax(DistanceValue start, DistanceValue end, WeightValue weight);

DistanceValue SafeSum(DistanceValue d, WeightValue w);

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<DistanceValue> FordBellman(const Graph& graph, int root);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int vertex_num, edge_num, root;
  input >> vertex_num >> edge_num >> root;
  --root;
  Graph graph(vertex_num);
  while (edge_num--) {
    int start, end;
    int64_t w;
    input >> start >> end >> w;
    --start;
    --end;
    graph[start].push_back({end, WeightValue{w}});
  }
  std::vector<DistanceValue> distances = FordBellman(graph, root);
  for (const auto& el : distances) {
    switch (el.state) {
      case DistanceState::kAbsent: {
        std::cout << "*\n";
        break;
      }
      case DistanceState::kNoMinimum: {
        std::cout << "-\n";
        break;
      }
      case DistanceState::kValid: {
        if (el.is_positive) {
          std::cout << el.abs_val << '\n';
        } else {
          std::cout << '-' << el.abs_val << '\n';
        }
        break;
      }
      default:
        throw;
    }
  }
}

DistanceValue SafeSum(DistanceValue d, WeightValue w) {
  DistanceValue res;
  if (d.state == DistanceState::kAbsent) return res;
  if (d.state == DistanceState::kNoMinimum) {
    res.state = DistanceState::kNoMinimum;
    return res;
  }
  if (d.is_positive == w.is_positive) {
    res.abs_val = d.abs_val + w.abs_val;
    res.is_positive = d.is_positive;
  } else {
    if (!w.is_positive) {
      if (w.abs_val <= d.abs_val) {
        res.abs_val = d.abs_val - w.abs_val;
        res.is_positive = true;
      } else {
        res.abs_val = w.abs_val - d.abs_val;
        res.is_positive = false;
      }
    } else {
      if (d.abs_val <= w.abs_val) {
        res.abs_val = w.abs_val - d.abs_val;
        res.is_positive = true;
      } else {
        res.abs_val = d.abs_val - w.abs_val;
        res.is_positive = false;
      }
    }
  }
  res.state = DistanceState::kValid;
  return res;
}

DistanceValue Relax(DistanceValue start, DistanceValue end,
                    WeightValue weight) {
  if (end.state == DistanceState::kNoMinimum) return end;
  DistanceValue candidate = SafeSum(start, weight);
  if (end.state == DistanceState::kAbsent) return candidate;
  if (candidate.state == DistanceState::kAbsent) return end;
  if (candidate.state == DistanceState::kNoMinimum) return candidate;
  if (candidate.is_positive == end.is_positive) {
    if (end.is_positive)
      return end.abs_val < candidate.abs_val ? end : candidate;
    return end.abs_val < candidate.abs_val ? candidate : end;
  }
  return candidate.is_positive ? end : candidate;
}

std::vector<DistanceValue> FordBellman(const Graph& graph, int root) {
  std::vector<DistanceValue> distances(graph.size());
  distances[root] = {0, true, DistanceState::kValid};
  int iteration_count = graph.size() - 1;
  while (iteration_count--) {
    for (int start = 0; start < graph.size(); ++start) {
      for (const auto& end : graph[start]) {
        distances[end.id] =
            Relax(distances[start], distances[end.id], end.weight);
      }
    }
  }
  // Check for negative cycles
  iteration_count = graph.size() - 1;
  while (iteration_count--) {
    for (int start = 0; start < graph.size(); ++start) {
      for (const auto& end : graph[start]) {
        DistanceValue curr_value = distances[end.id];
        DistanceValue new_value =
            Relax(distances[start], distances[end.id], end.weight);
        if (curr_value != new_value) {
          distances[end.id] = new_value;
          distances[end.id].state = DistanceState::kNoMinimum;
        }
      }
    }
  }
  return distances;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6 7 1
1 2 10
2 3 5
1 3 100
3 5 7
5 4 10
4 3 -18
6 1 -1
)";
    Solution(ss);
    std::cout << "expected = 0; 10; -; -; -; *\n";
  }
}
