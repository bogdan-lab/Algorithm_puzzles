#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

constexpr int kInfinity = std::numeric_limits<int>::max();
constexpr int kMinusInfinity = std::numeric_limits<int>::min();

struct Node {
  Node(int gid) : id(gid), leader(gid), min(gid), max(gid), size(1) {}

  int id;
  int leader;
  int min = kInfinity;
  int max = kMinusInfinity;
  int size = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();

void PrintSetData(std::vector<Node>& data, int id);
int FindLeader(std::vector<Node>& data, int id);
void Union(std::vector<Node>& data, int lhs, int rhs);
void Connect(std::vector<Node>& data, int src, int dst);

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
  std::vector<Node> data;
  data.reserve(n);
  for (int i = 0; i < n; ++i) {
    data.emplace_back(i);
  }
  std::string command;
  while (input >> command) {
    if (command == "get") {
      int id;
      input >> id;
      PrintSetData(data, --id);
    } else {
      int lhs, rhs;
      input >> lhs >> rhs;
      Union(data, --lhs, --rhs);
    }
  }
}

int FindLeader(std::vector<Node>& data, int id) {
  if (data[id].leader == id) return id;
  data[id].leader = FindLeader(data, data[id].leader);
  return data[id].leader;
}

void PrintSetData(std::vector<Node>& data, int id) {
  id = FindLeader(data, id);
  std::cout << data[id].min + 1 << ' ' << data[id].max + 1 << ' '
            << data[id].size << '\n';
}

void Connect(std::vector<Node>& data, int src, int dst) {
  data[src].leader = dst;
  data[dst].min = std::min(data[dst].min, data[src].min);
  data[dst].max = std::max(data[dst].max, data[src].max);
  data[dst].size = data[dst].size + data[src].size;
}

void Union(std::vector<Node>& data, int lhs, int rhs) {
  int lhs_leader = FindLeader(data, lhs);
  int rhs_leader = FindLeader(data, rhs);
  if (lhs_leader == rhs_leader) return;
  if (data[lhs_leader].size > data[rhs_leader].size) {
    Connect(data, rhs_leader, lhs_leader);
  } else {
    Connect(data, lhs_leader, rhs_leader);
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
union 1 2
get 3
get 2
union 2 3
get 2
union 1 3
get 5
union 4 5
get 5
union 4 1
get 5
)";
    Solution(ss);
    std::cout << R"(====== expected ======
3 3 1
1 2 2
1 3 3
5 5 1
4 5 2
1 5 5
 )";
  }
}
