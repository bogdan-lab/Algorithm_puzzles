#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct Monster {
  size_t idx = 0;
  size_t health = 0;
  size_t damage = 0;
};

struct Effectivity {
  size_t cost = 0;
  size_t gain = 0;
  size_t last_idx = 0;
};

void solution(std::istream& input = std::cin);
void run_tests();
size_t count_shots(const std::vector<Monster>& data);
size_t next_idx(size_t idx, size_t size);
size_t prev_idx(size_t idx, size_t size);
std::vector<Effectivity> calc_effectivenes(const std::vector<Monster>& data);

int main() {
  //run_tests();
   solution(std::cin);
  return 0;
}

size_t next_idx(size_t idx, size_t size) { return ++idx == size ? 0 : idx; }
size_t prev_idx(size_t idx, size_t size) {
  return idx == 0 ? size - 1 : idx - 1;
}

std::vector<Effectivity> calc_effectivenes(const std::vector<Monster>& data) {
  std::vector<Effectivity> res(data.size());
  // effectiveness for 0 element
  size_t idx = 0;
  size_t next = 1;
  res[0].cost = data[0].health;
  while (data[idx].damage >= data[next].health && next != 0) {
    idx = next;
    next = next_idx(next, data.size());
    res[0].gain += data[idx].health;
  }
  if (next != 0) {
    res[0].gain += data[idx].damage;
    res[0].last_idx = next;
  } else {
    size_t prev = prev_idx(0, data.size());
    res[0].gain -= std::min(data[0].health, data[prev].damage);
    res[0].last_idx = prev;
  }
  // going backward and getting all effectiveties!
  for (size_t i = data.size() - 1; i > 0; --i) {
    res[i].cost = data[i].health;
    size_t nxt = next_idx(i, data.size());
    if (data[i].damage >= data[nxt].health) {
      res[i].gain = data[nxt].health + res[nxt].gain;
      res[i].last_idx = res[nxt].last_idx;
      if (res[nxt].last_idx == i) {
        size_t prev = prev_idx(i, data.size());
        res[i].gain -= std::min(data[i].health, data[prev].damage);
        res[i].last_idx = prev;
      }
    } else {
      res[i].gain = data[i].damage;
      res[i].last_idx = nxt;
    }
  }
  return res;
}

size_t count_shots(const std::vector<Monster>& data) {
  auto it = std::min_element(
      data.begin(), data.end(), [](const Monster& lhs, const Monster& rhs) {
        return lhs.health < rhs.health ||
               (lhs.health == rhs.health && lhs.damage > rhs.damage);
      });

  size_t start_idx = it->idx;
  size_t count = it->health;
  size_t idx = next_idx(start_idx, data.size());
  size_t prev_idx = start_idx;
  while (idx != start_idx) {
    count += data[prev_idx].damage >= data[idx].health
                 ? 0
                 : data[idx].health - data[prev_idx].damage;
    prev_idx = idx;
    idx = next_idx(idx, data.size());
  }
  return count;
}

void solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    size_t n;
    input >> n;
    std::vector<Monster> data;
    data.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      size_t a, b;
      input >> a >> b;
      data.push_back({.idx = i, .health = a, .damage = b});
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
      ss <<R"(4
6 8
9 3
8 1
9 7
)";
    solution(ss);
    std::cout << "expected = 15\n";
  }
}
