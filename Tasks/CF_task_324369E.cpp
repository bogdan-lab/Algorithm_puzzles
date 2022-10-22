#include <iostream>
#include <sstream>
#include <vector>

struct Req {
  int l = 0;
  int r = 0;
  int64_t d = 0;
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

void Solution(std::istream& input) {
  int n, m, k;
  input >> n >> m >> k;
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }
  std::vector<Req> req(m);
  for (auto& el : req) {
    input >> el.l >> el.r >> el.d;
    --el.l;
  }
  std::vector<int64_t> diff_req(req.size());
  while (k--) {
    int x, y;
    input >> x >> y;
    --x;
    ++diff_req[x];
    if (y < diff_req.size()) {
      --diff_req[y];
    }
  }

  std::vector<int64_t> prefix_req(req.size() + 1);
  for (int i = 1; i < prefix_req.size(); ++i) {
    prefix_req[i] = prefix_req[i - 1] + diff_req[i - 1];
  }

  for (int i = 0; i < req.size(); ++i) {
    req[i].d *= prefix_req[i + 1];
  }

  std::vector<int64_t> diff(data.size());

  for (int i = 0; i < req.size(); ++i) {
    diff[req[i].l] += req[i].d;
    if (req[i].r < diff.size()) {
      diff[req[i].r] -= req[i].d;
    }
  }

  std::vector<int64_t> prefix(data.size() + 1);
  for (int i = 1; i < prefix.size(); ++i) {
    prefix[i] = prefix[i - 1] + diff[i - 1];
  }
  for (int i = 0; i < data.size(); ++i) {
    std::cout << data[i] + prefix[i + 1] << ' ';
  }
  std::cout << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 3 3
1 2 3
1 2 1
1 3 2
2 3 4
1 2
1 3
2 3
)";
    Solution(ss);
    std::cout << "expected = 9; 18; 17\n";
  }
  {
    std::stringstream ss;
    ss << R"(1 1 1
1
1 1 1
1 1
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 3 6
1 2 3 4
1 2 1
2 3 2
3 4 4
1 2
1 3
2 3
1 2
1 3
2 3
)";
    Solution(ss);
    std::cout << "expected = 5 18 31 20\n";
  }
}
