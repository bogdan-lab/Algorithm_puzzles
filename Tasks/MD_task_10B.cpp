#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

using Graph = std::vector<std::stack<int>>;

void Solution(std::istream& input = std::cin);
void RunTests();

void ToLower(std::string& str);
int GetNameId(const std::string& name,
              std::unordered_map<std::string, int>& table, int& curr_id);
void AddEdgeToGraph(Graph& graph, int from_id, int to_id);
int GetMaxLength(Graph graph);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::string name_to, name_from, request;
  std::unordered_map<std::string, int> name_to_id;
  int curr_id = 0;
  Graph graph;
  while (n--) {
    input >> name_to >> request >> name_from;
    ToLower(name_to);
    ToLower(name_from);
    // Guarantee that Polycarp will have id = 0
    int from_id = GetNameId(name_from, name_to_id, curr_id);
    int to_id = GetNameId(name_to, name_to_id, curr_id);
    AddEdgeToGraph(graph, from_id, to_id);
  }
  std::cout << GetMaxLength(std::move(graph)) + 1 << '\n';
}

int GetMaxLength(Graph graph) {
  std::vector<int> lookup(graph.size());
  std::vector<int> distance(graph.size());
  std::stack<int> buff;
  buff.push(0);
  lookup[0] = 1;
  while (!buff.empty()) {
    int top_id = buff.top();
    while (!graph[top_id].empty() && lookup[graph[top_id].top()] == 1) {
      graph[top_id].pop();
    }
    if (graph[top_id].empty()) {
      // I am in the bottom
      buff.pop();
    } else {
      // I can go deeper
      int next_id = graph[top_id].top();
      graph[top_id].pop();
      buff.push(next_id);
      lookup[next_id] = 1;
      distance[next_id] = distance[top_id] + 1;
    }
  }
  return *std::max_element(distance.begin(), distance.end());
}

void AddEdgeToGraph(Graph& graph, int from_id, int to_id) {
  int max_id = std::max(from_id, to_id);
  if (graph.size() <= max_id) {
    graph.resize(max_id + 1);
  }
  graph[from_id].push(to_id);
}

int GetNameId(const std::string& name,
              std::unordered_map<std::string, int>& table, int& curr_id) {
  auto it = table.find(name);
  if (it == table.end()) {
    table.emplace(name, curr_id);
    return curr_id++;
  }
  return it->second;
}

void ToLower(std::string& str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](char c) { return std::tolower(c); });
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
tourist reposted Polycarp
Petr reposted Tourist
WJMZBMR reposted Petr
sdya reposted wjmzbmr
vepifanov reposted sdya
)";
    Solution(ss);
    std::cout << "expected = 6\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
Mike reposted Polycarp
Max reposted Polycarp
EveryOne reposted Polycarp
111 reposted Polycarp
VkCup reposted Polycarp
Codeforces reposted Polycarp
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(1
SoMeStRaNgEgUe reposted PoLyCaRp
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
}
