#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

bool IsConnected(const std::string& l, const std::string& r) {
  return l.back() == r.front();
}

std::vector<std::vector<int>> BuildGraph(
    const std::vector<std::string>& str_data) {
  std::vector<std::vector<int>> res(str_data.size());
  for (int i = 0; i < str_data.size(); ++i) {
    for (int j = 0; j < str_data.size(); ++j) {
      if (IsConnected(str_data[i], str_data[j])) {
        res[i].push_back(j);
      }
    }
  }
  return res;
}

std::vector<int> GetDistances(const std::vector<std::vector<int>>& graph,
                              int root) {
  std::vector<uint8_t> lookup(graph.size());
  std::queue<int> buff;
  buff.push(root);
  lookup[root] = 1;
  std::vector<int> d(graph.size(), std::numeric_limits<int>::max());
  d[root] = 1;
  while (!buff.empty()) {
    int c = buff.front();
    buff.pop();
    for (const auto& id : graph[c]) {
      if (lookup[id]) continue;
      lookup[id] = 1;
      d[id] = d[c] + 1;
      buff.push(id);
    }
  }
  return d;
}

void DFS(const std::vector<std::vector<int>>& graph, int par,
         std::vector<int>& lookup, std::vector<int>& dist,
         std::vector<int>& is_leaf) {
  bool has_child = false;
  for (const auto& id : graph[par]) {
    if (lookup[id]) continue;
    lookup[id] = 1;
    has_child = true;
    dist[id] = dist[par] + 1;
    DFS(graph, id, lookup, dist, is_leaf);
    lookup[id] = 0;
  }
  if (!has_child) {
    is_leaf[par] = 1;
  }
}

int GetDFSDistance(const std::vector<std::vector<int>>& graph, int root) {
  std::vector<int> is_leaf(graph.size());
  std::vector<int> dist(graph.size(), std::numeric_limits<int>::max());
  std::vector<int> lookup(graph.size());
  lookup[root] = 1;
  dist[root] = 1;

  DFS(graph, root, lookup, dist, is_leaf);

  int min_len = std::numeric_limits<int>::max();
  for (int i = 0; i < dist.size(); ++i) {
    if (is_leaf[i]) {
      min_len = std::min(min_len, dist[i]);
    }
  }
  return min_len;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<std::string> str_data(n);
  for (auto& el : str_data) {
    input >> el;
  }

  std::vector<std::vector<int>> graph = BuildGraph(str_data);

  int min_len = std::numeric_limits<int>::max();
  for (int i = 0; i < graph.size(); ++i) {
    min_len = std::min(min_len, GetDFSDistance(graph, i));
  }

  if (min_len % 2) {
    std::cout << "First\n";
  } else {
    std::cout << "Second\n";
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
enum
float
if
modint
takahashi
template
)";
    Solution(ss);
    std::cout << "expected = First\n";
  }
  {
    std::stringstream ss;
    ss << R"(10
catch
chokudai
class
continue
copy
exec
havoc
intrinsic
static
yucatec
)";
    Solution(ss);
    std::cout << "expected = Second\n";
  }
  {
    std::stringstream ss;
    ss << R"(16
mnofcmzsdx
lgeowlxuqm
ouimgdjxlo
jhwttcycwl
jbcuioqbsj
mdjfikdwix
jhvdpuxfil
peekycgxco
sbvxszools
xuuqebcrzp
jsciwvdqzl
obblxzjhco
ptobhnpfpo
muizaqtpgx
jtgjnbtzcl
sivwidaszs
)";
    Solution(ss);
    std::cout << "expected = First\n";
  }
}
