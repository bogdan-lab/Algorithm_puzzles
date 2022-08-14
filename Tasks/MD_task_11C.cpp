#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr int kInfinity = std::numeric_limits<int>::max();
constexpr int kNegativeInfinity = std::numeric_limits<int>::min();
constexpr int kAbsentId = -1;
constexpr int kAbsentEdge = 100'000;

using GraphMatrix = std::vector<std::vector<int>>;

struct FloydResult {
  FloydResult(const GraphMatrix& weights)
      : length(weights),
        next(weights.size(), std::vector<int>(weights.size(), kAbsentId)) {
    for (int start = 0; start < weights.size(); ++start) {
      for (int end = 0; end < weights.size(); ++end) {
        if (length[start][end] != kInfinity) {
          next[start][end] = end;
        }
      }
    }
  }

  GraphMatrix length;
  GraphMatrix next;
};

FloydResult FindNegativeCycle(const GraphMatrix& weights);
void FixReadValue(int& el) { el = el == kAbsentEdge ? kInfinity : el; }
int SafeSum(int lhs, int rhs);
std::vector<int> GetNegativeCycle(const FloydResult& length);
bool BuildNegativeCycle(int id, const GraphMatrix& next,
                        std::vector<int>& path);

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
  int vertex_num;
  input >> vertex_num;
  GraphMatrix weights(vertex_num);
  for (auto& row : weights) {
    row.resize(vertex_num);
    for (auto& el : row) {
      input >> el;
      FixReadValue(el);
    }
  }
  FloydResult floyd = FindNegativeCycle(weights);
  std::vector<int> path = GetNegativeCycle(floyd);
  if (path.empty()) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n" << path.size() << '\n';
    for (const auto& el : path) {
      std::cout << el + 1 << ' ';
    }
    std::cout << '\n';
  }
}

bool BuildNegativeCycle(int id, const GraphMatrix& next,
                        std::vector<int>& path) {
  int curr_id = next[id][id];
  int count = 0;
  while (curr_id != id && count < next.size()) {
    path.push_back(curr_id);
    curr_id = next[curr_id][id];
    ++count;
  }
  path.push_back(id);
  if (count == next.size()) {
    path.clear();
    return false;
  }
  return true;
}

std::vector<int> GetNegativeCycle(const FloydResult& floyd) {
  std::vector<int> path;
  path.reserve(floyd.length.size());
  for (int i = 0; i < floyd.length.size(); ++i) {
    if (floyd.length[i][i] < 0 && BuildNegativeCycle(i, floyd.next, path)) {
      return path;
    }
  }
  return path;
}

int SafeSum(int lhs, int rhs) {
  if (lhs == kInfinity) return lhs;
  if (rhs == kInfinity) return rhs;
  int64_t diff_check = static_cast<int64_t>(lhs) + static_cast<int64_t>(rhs);
  if (diff_check < kNegativeInfinity) return kNegativeInfinity;
  return lhs + rhs;
}

FloydResult FindNegativeCycle(const GraphMatrix& weights) {
  FloydResult res(weights);
  for (int mid = 0; mid < weights.size(); ++mid) {
    for (int start = 0; start < weights.size(); ++start) {
      for (int end = 0; end < weights.size(); ++end) {
        int new_length = SafeSum(res.length[start][mid], res.length[mid][end]);
        if (new_length < res.length[start][end]) {
          res.length[start][end] = new_length;
          res.next[start][end] = res.next[start][mid];
        }
      }
    }
  }
  return res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
0 -1
-1 0
)";
    Solution(ss);
    std::cout << "expected = YES; 2; 2 1\n";
  }
}
