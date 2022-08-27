#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <vector>

struct EdgeChange {
  int start = -1;
  int end = -1;
  int change = -1;
};

bool operator<(EdgeChange l, EdgeChange r) {
  return std::tie(l.start, l.end) < std::tie(r.start, r.end);
}

int CalculateFlux(std::vector<std::unordered_map<int, int>>& data, int start,
                  int end);
std::vector<EdgeChange> BFS(
    const std::vector<std::unordered_map<int, int>>& data, int start, int end);
std::vector<EdgeChange> GetPath(const std::vector<EdgeChange>& parents,
                                int start, int end);

void Solution(std::istream& input = std::cin);
void RunTests();

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
  std::vector<std::unordered_map<int, int>> graph(vertex_num);
  while (edge_num--) {
    int l, w, r;
    input >> l >> r >> w;
    --l;
    --r;
    graph[l][r] += w;
    graph[r][l] += w;
  }

  std::cout << CalculateFlux(graph, 0, vertex_num - 1) << '\n';
}

std::vector<EdgeChange> GetPath(const std::vector<EdgeChange>& bfs_res,
                                int start, int end) {
  std::vector<EdgeChange> result;
  int cid = end;
  while (cid != start) {
    result.push_back(bfs_res[cid]);
    cid = bfs_res[cid].start;
  }
  std::reverse(result.begin(), result.end());
  return result;
}

int CalculateFlux(std::vector<std::unordered_map<int, int>>& data, int start,
                  int end) {
  // Find path by BFS
  std::vector<EdgeChange> bfs_res = BFS(data, start, end);
  if (bfs_res[end].start == -1) return 0;
  // Find minimum change in the path
  std::vector<EdgeChange> path = GetPath(bfs_res, start, end);
  int min_change = std::min_element(path.begin(), path.end(),
                                    [](EdgeChange l, EdgeChange r) {
                                      return l.change < r.change;
                                    })
                       ->change;
  std::for_each(path.begin(), path.end(),
                [min_change](EdgeChange& el) { el.change = min_change; });
  // Adding flux to the right will result in flux creation to the left
  int initial_size = path.size();
  for (int i = 0; i < initial_size; ++i) {
    path.push_back(path[i]);
    std::swap(path.back().start, path.back().end);
    path.back().change *= -1;
  }
  // Modify data according to the minimum change
  for (const auto& el : path) {
    data[el.start][el.end] -= el.change;
    if (!data[el.start][el.end]) {
      data[el.start].erase(el.end);
    }
  }
  return min_change + CalculateFlux(data, start, end);
}

std::vector<EdgeChange> BFS(
    const std::vector<std::unordered_map<int, int>>& data, int start, int end) {
  std::vector<EdgeChange> parent(data.size());
  std::vector<int> lookup(data.size());
  std::queue<int> buff;
  buff.push(start);
  while (!buff.empty()) {
    int top_id = buff.front();
    if (top_id == end) break;
    buff.pop();
    for (const auto& e : data[top_id]) {
      if (!lookup[e.first]) {
        lookup[e.first] = 1;
        buff.push(e.first);
        parent[e.first] = {.start = top_id, .end = e.first, .change = e.second};
      }
    }
  }
  return parent;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
2
1 2 1
2 1 3
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
}
