#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Node {
  explicit Node(int gid) : id(gid), leader(gid) {}
  int id;
  int leader;
  int exp = 0;
  int rank = 1;
};

struct IdExp {
  int id = 0;
  int exp = 0;
};

IdExp FindLeader(std::vector<Node>& data, int id);
void Join(std::vector<Node>& data, int lhs, int rhs);
void Connect(std::vector<Node>& data, int src, int dst);

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
  int el_num, req_num;
  input >> el_num >> req_num;
  std::vector<Node> data;
  data.reserve(el_num);
  for (int i = 0; i < el_num; ++i) {
    data.emplace_back(i);
  }
  std::string command;
  while (req_num--) {
    input >> command;
    if (command == "add") {
      int id, exp;
      input >> id >> exp;
      int leader = FindLeader(data, --id).id;
      data[leader].exp += exp;
    } else if (command == "get") {
      int id;
      input >> id;
      std::cout << FindLeader(data, --id).exp << '\n';
    } else {
      int idl, idr;
      input >> idl >> idr;
      Join(data, --idl, --idr);
    }
  }
}

IdExp FindLeader(std::vector<Node>& data, int id) {
  if (id == data[id].leader) return {id, data[id].exp};
  IdExp res = FindLeader(data, data[id].leader);
  data[id].leader = res.id;
  int total_exp = res.exp + data[id].exp;
  data[id].exp += res.exp - data[res.id].exp;
  return {data[id].leader, total_exp};
}

void Join(std::vector<Node>& data, int lhs, int rhs) {
  int lhs_leader = FindLeader(data, lhs).id;
  int rhs_leader = FindLeader(data, rhs).id;
  if (lhs_leader == rhs_leader) return;
  if (data[lhs_leader].rank > data[rhs_leader].rank) {
    Connect(data, rhs_leader, lhs_leader);
  } else {
    Connect(data, lhs_leader, rhs_leader);
  }
}

void Connect(std::vector<Node>& data, int src, int dst) {
  data[src].leader = data[dst].id;
  data[src].exp -= data[dst].exp;
  data[dst].rank = std::max(data[src].rank, data[dst].rank);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 6
add 1 100
join 1 3
add 1 50
get 1
get 2
get 3
)";
    Solution(ss);
    std::cout << "expected = 150; 0; 50\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 19
add 1 1
add 2 2
add 3 3
add 4 4
add 5 5
get 1
get 2
get 3
get 4
get 5
join 1 2
join 2 3
join 1 4
join 2 5
get 1
get 2
get 3
get 4
get 5
)";
    Solution(ss);
    std::cout << "expected = 1 2 3 4 5; 1 2 3 4 5\n";
  }
}
