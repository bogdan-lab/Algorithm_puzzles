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
uint64_t GetMaxPretty(const Graph& data, const std::vector<Node>& values);
uint64_t DFS(const Graph& data, const std::vector<Node>& values,
             bool left_on_start);
uint64_t GetBestValue(uint64_t curr_val, uint64_t lo, uint64_t hi);

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
    std::cout << GetMaxPretty(data, values) << '\n';
  }
}

uint64_t GetMaxPretty(const Graph& data, const std::vector<Node>& values) {
  return std::max(DFS(data, values, /*left_on_start=*/true),
                  DFS(data, values, /*left_on_start=*/false));
}

uint64_t DFS(const Graph& data, const std::vector<Node>& values,
             bool left_on_start) {
  uint64_t max_pretty = 0;
  std::vector<uint64_t> chosen_values(data.size());
  std::stack<int> buffer;
  chosen_values[0] = left_on_start ? values[0].left : values[0].right;
  buffer.push(0);
  while (!buffer.empty()) {
    int curr_id = buffer.top();
    int next_id = std::numeric_limits<int>::max();
    for (const auto& id : data[curr_id]) {
      if (!chosen_values[id]) {
        next_id = id;
        break;
      }
    }
    if (next_id >= chosen_values.size()) {
      buffer.pop();
    } else {
      chosen_values[next_id] = GetBestValue(
          chosen_values[curr_id], values[next_id].left, values[next_id].right);
      max_pretty += chosen_values[next_id] > chosen_values[curr_id]
                        ? chosen_values[next_id] - chosen_values[curr_id]
                        : chosen_values[curr_id] - chosen_values[next_id];
      buffer.push(next_id);
    }
  }
  return max_pretty;
}

uint64_t GetBestValue(uint64_t curr_val, uint64_t lo, uint64_t hi) {
  if (curr_val <= lo) return hi;
  if (curr_val >= hi) return lo;
  return curr_val - lo < hi - curr_val ? hi : lo;
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
