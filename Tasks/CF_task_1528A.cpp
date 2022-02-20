#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <stack>
#include <vector>

using Graph = std::vector<std::vector<int>>;

struct Node {
  uint64_t left = 0;
  uint64_t right = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();
Graph DFS(const Graph& data);
uint64_t AbsDiff(uint64_t lhs, uint64_t rhs);

uint64_t CalcSubtree(const Graph& direct_data, const std::vector<Node>& values,
                     std::vector<Node>& subtree_results, int root,
                     bool is_left);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t = 0;
  input >> t;
  while (t--) {
    int n = 0;
    input >> n;
    std::vector<Node> values(n);
    for (auto& el : values) {
      input >> el.left >> el.right;
    }
    Graph data(n);
    int edge_num = n - 1;
    while (edge_num--) {
      int left, right;
      input >> left >> right;
      --left;
      --right;
      data[left].push_back(right);
      data[right].push_back(left);
    }
    Graph direct_data = DFS(data);
    std::vector<Node> subtree_results(data.size());
    std::cout << std::max(CalcSubtree(direct_data, values, subtree_results,
                                      /*root=*/0, /*is_left=*/true),
                          CalcSubtree(direct_data, values, subtree_results,
                                      /*root=*/0, /*is_left=*/false))
              << '\n';
  }
}

uint64_t AbsDiff(uint64_t lhs, uint64_t rhs) {
  return lhs > rhs ? lhs - rhs : rhs - lhs;
}

uint64_t CalcSubtree(const Graph& direct_data, const std::vector<Node>& values,
                     std::vector<Node>& subtree_results, int root,
                     bool is_left) {
  if (direct_data[root].empty()) {
    return 0;
  }
  if (is_left) {
    if (!subtree_results[root].left) {
      for (const auto& id : direct_data[root]) {
        subtree_results[root].left +=
            std::max(AbsDiff(values[root].left, values[id].left) +
                         CalcSubtree(direct_data, values, subtree_results, id,
                                     /*is_left=*/true),
                     AbsDiff(values[root].left, values[id].right) +
                         CalcSubtree(direct_data, values, subtree_results, id,
                                     /*is_left=*/false));
      }
    }
    return subtree_results[root].left;
  } else {
    if (!subtree_results[root].right) {
      for (const auto& id : direct_data[root]) {
        subtree_results[root].right +=
            std::max(AbsDiff(values[root].right, values[id].left) +
                         CalcSubtree(direct_data, values, subtree_results, id,
                                     /*is_left=*/true),
                     AbsDiff(values[root].right, values[id].right) +
                         CalcSubtree(direct_data, values, subtree_results, id,
                                     /*is_left=*/false));
      }
    }
    return subtree_results[root].right;
  }
}

Graph DFS(const Graph& data) {
  Graph dfs_res(data.size());
  std::vector<uint8_t> visited(data.size());
  std::stack<int> buffer;
  visited[0] = 1;
  buffer.push(0);
  while (!buffer.empty()) {
    int curr_id = buffer.top();
    int next_id = std::numeric_limits<int>::max();
    for (const auto& id : data[curr_id]) {
      if (!visited[id]) {
        next_id = id;
        break;
      }
    }
    if (next_id >= visited.size()) {
      buffer.pop();
    } else {
      visited[next_id] = 1;
      dfs_res[curr_id].push_back(next_id);
      buffer.push(next_id);
    }
  }
  return dfs_res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
2
1 6
3 8
1 2
3
1 3
4 6
7 9
1 2
2 3
6
3 14
12 20
12 19
2 12
10 17
3 17
3 2
6 5
1 5
2 6
4 6
)";
    Solution(ss);
    std::cout << "expected = 7; 8; 62\n";
  }
}
