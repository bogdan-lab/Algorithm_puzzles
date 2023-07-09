#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

struct Insurance {
  int owner;
  int layers;
};

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

Graph BuildGraph(const std::vector<int>& data) {
  Graph res(data.size() + 1);
  for (size_t i = 0; i < data.size(); ++i) {
    res[data[i]].push_back(i + 1);
  }
  return res;
}

std::vector<int> GetInitialChildrenIns(const std::vector<Insurance>& data,
                                       size_t size) {
  std::vector<int> res(size);
  for (const auto& el : data) {
    res[el.owner] = std::max(res[el.owner], el.layers + 1);
  }
  return res;
}

void DFS(size_t id, const Graph& g, std::vector<int>& push_data,
         std::vector<int8_t>& has_ins, std::vector<int8_t>& lookup) {
  if (lookup[id]) return;
  lookup[id] = 1;

  if (push_data[id] > 0) {
    has_ins[id] = 1;
    --push_data[id];
  }

  for (const auto& nid : g[id]) {
    if (push_data[id] > 0) {
      push_data[nid] = std::max(push_data[id], push_data[nid]);
    }
    DFS(nid, g, push_data, has_ins, lookup);
  }
}

size_t DFSCount(const Graph& g, std::vector<int>& push_data) {
  std::vector<int8_t> lookup(g.size());
  std::vector<int8_t> has_ins(g.size());

  DFS(0, g, push_data, has_ins, lookup);

  return std::count(has_ins.begin(), has_ins.end(), 1);
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;

  std::vector<int> parents(n - 1);
  for (auto& el : parents) {
    input >> el;
    --el;
  }

  std::vector<Insurance> ins(m);
  for (auto& el : ins) {
    input >> el.owner >> el.layers;
    --el.owner;
  }

  Graph g = BuildGraph(parents);

  std::vector<int> push_data = GetInitialChildrenIns(ins, g.size());

  std::cout << DFSCount(g, push_data) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(7 3
1 2 1 3 3 3
1 1
1 2
4 3
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
}
