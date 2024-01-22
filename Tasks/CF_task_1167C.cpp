#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

struct GrPer {
  int group;
  int person;
};

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //   RunTests();
  Solution(std::cin);
  return 0;
}

std::vector<int> DFS(std::vector<std::stack<int>>& g_to_f, int person_count) {
  std::vector<uint8_t> lookup(person_count, 0);

  std::vector<int> totals(person_count, 0);
  for (int i = 0; i < g_to_f.size(); ++i) {
    if (g_to_f[i].empty()) {
      continue;
    }
    std::vector<int> curr_persons;
    int curr_total = 0;
    int root = g_to_f[i].top();
    g_to_f[i].pop();
    lookup[root] = 1;
    std::stack<GrPer> buff;
    buff.push({i, root});
    while (!buff.empty()) {
      GrPer gr_per = buff.top();
      while (!g_to_f[gr_per.group].empty() &&
             lookup[g_to_f[gr_per.group].top()] == 1) {
        g_to_f[gr_per.person].pop();
      }
      if (g_to_f[gr_per.group].empty()) {
        curr_total += 1;
        curr_persons.push_back(gr_per.person);
        buff.pop();
      } else {
        GrPer next{gr_per.group, g_to_f[gr_per.group].top()};
        g_to_f[gr_per.group].pop();
        lookup[next.person] = 1;
        buff.push(next);
      }
    }

    for (const auto p : curr_persons) {
      totals[p] = curr_total;
    }
  }
  return totals;
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;

  std::vector<std::stack<int>> groups_to_fr(m);
  for (int i = 0; i < m; ++i) {
    int count = 0;
    input >> count;
    while (--count) {
      int id = -1;
      input >> id;
      groups_to_fr[i].push(id);
    }
  }

  std::vector<int> res = DFS(groups_to_fr, n);
  for (const auto r : res) {
    std::cout << r << ' ';
  }
  std::cout << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(
        7 5
3 2 5 4
0
2 1 2
1 1
2 6 7
    )";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
