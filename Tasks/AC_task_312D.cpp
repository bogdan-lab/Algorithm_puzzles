#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

constexpr uint64_t kMod = 998244353;

struct Node {
  uint64_t left = 0;
  uint64_t right = 0;
  uint64_t count = 0;
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

size_t Left(size_t i) { return 2 * i + 1; }

size_t Right(size_t i) { return 2 * i + 2; }

uint64_t GetNextPow2(uint64_t val) {
  uint64_t p = 2;
  while (val > p) {
    p *= 2;
  }
  return p;
}

void Merge(const std::vector<Node>& l, const std::vector<Node>& r,
           std::vector<Node>& res) {
  std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>> mp;
  for (size_t i = 0; i < l.size(); ++i) {
    for (size_t j = 0; j < r.size(); ++j) {
      const auto& ln = l[i];
      const auto& rn = r[j];

      uint64_t neut = rn.right <= ln.left ? rn.right : ln.left;
      uint64_t n_l = rn.left + ln.left - neut;
      uint64_t n_r = ln.right + rn.right - neut;
      uint64_t n_count = ((ln.count % kMod) * (rn.count % kMod)) % kMod;

      mp[n_l][n_r] = (mp[n_l][n_r] + n_count) % kMod;
    }
  }

  for (const auto& el : mp) {
    for (const auto& inn : el.second) {
      res.push_back(
          {.left = el.first, .right = inn.first, .count = inn.second});
    }
  }
}

void Solution(std::istream& input) {
  std::string data;
  input >> data;

  uint64_t power = GetNextPow2(data.size());
  uint64_t total_size = 2 * power - 1;

  std::vector<std::vector<Node>> tree(total_size);

  for (size_t i = power - 1, j = 0; i < tree.size(); ++i, ++j) {
    if (j < data.size()) {
      if (data[j] == '(') {
        tree[i].push_back({.left = 1, .count = 1});
      } else if (data[j] == ')') {
        tree[i].push_back({.right = 1, .count = 1});
      } else {
        tree[i].push_back({.left = 1, .count = 1});
        tree[i].push_back({.right = 1, .count = 1});
      }
    } else {
      tree[i].push_back({.count = 1});
    }
  }

  for (int i = power - 2; i >= 0; --i) {
    Merge(tree[Left(i)], tree[Right(i)], tree[i]);
  }

  auto it = std::find_if(tree[0].begin(), tree[0].end(), [](const Node& node) {
    return node.left == 0 && node.right == 0;
  });
  if (it == tree[0].end()) {
    std::cout << 0 << '\n';
  } else {
    std::cout << it->count << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
