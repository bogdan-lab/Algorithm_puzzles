#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct Monster {
  uint64_t health = 0;
  uint64_t damage = 0;
};

void solution(std::istream& input = std::cin);
void run_tests();
uint64_t count_shots(const std::vector<Monster>& data);
uint64_t next_idx(uint64_t idx, uint64_t size);
uint64_t prev_idx(uint64_t idx, uint64_t size);
uint64_t calc_cost(uint64_t idx, const std::vector<Monster>& data);

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  //run_tests();
  solution(std::cin);
  return 0;
}

uint64_t next_idx(uint64_t idx, uint64_t size) {
  return ++idx == size ? 0 : idx;
}
uint64_t prev_idx(uint64_t idx, uint64_t size) {
  return idx == 0 ? size - 1 : idx - 1;
}

uint64_t calc_cost(uint64_t idx, const std::vector<Monster>& data) {
  uint64_t pidx = prev_idx(idx, data.size());
  return data[idx].health > data[pidx].damage
             ? data[idx].health - data[pidx].damage
             : 0;
}

uint64_t count_shots(const std::vector<Monster>& data) {
  uint64_t curr_count = data[0].health;
  for (uint64_t i = 1; i < data.size(); ++i) {
    curr_count += calc_cost(i, data);
  }
  uint64_t min_count = curr_count;

  for (uint64_t i = 1; i < data.size(); ++i) {
    curr_count += -calc_cost(i, data) - data[i - 1].health + data[i].health +
                  calc_cost(i - 1, data);
    min_count = std::min(curr_count, min_count);
  }
  return min_count;
}

void solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    uint64_t n;
    input >> n;
    std::vector<Monster> data;
    data.reserve(n);
    for (uint64_t i = 0; i < n; ++i) {
      uint64_t a, b;
      input >> a >> b;
      data.push_back({.health = a, .damage = b});
    }
    std::cout << count_shots(data) << '\n';
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(1
3
7 15
2 14
5 3
)";
    solution(ss);
    std::cout << "expected = 6\n";
  }
  {
    std::stringstream ss;
    ss << R"(1
8
7 4
9 10
4 8
3 1
1 7
9 5
1 4
2 5
)";
    solution(ss);
    std::cout << "expected = 10\n";
  }
  {
    std::stringstream ss;
    ss << R"(1
4
6 8
9 3
8 1
9 7
)";
    solution(ss);
    std::cout << "expected = 15\n";
  }
}
