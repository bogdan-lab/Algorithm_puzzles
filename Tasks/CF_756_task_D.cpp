#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr size_t kEmptyValue = std::numeric_limits<size_t>::max();

void Solution(std::istream& input = std::cin);
void RunTests();
std::vector<size_t> SolveOne(const std::vector<size_t>& parents,
                             const std::vector<size_t>& permut);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    size_t n;
    input >> n;
    std::vector<size_t> parents(n);
    for (auto& el : parents) {
      input >> el;
      --el;
    }
    std::vector<size_t> permut(n);
    for (auto& el : permut) {
      input >> el;
      --el;
    }
    auto res = SolveOne(parents, permut);
    if (res.empty()) {
      std::cout << "-1";
    } else {
      for (const auto& el : res) {
        std::cout << el << ' ';
      }
    }
    std::cout << '\n';
  }
}

std::vector<size_t> SolveOne(const std::vector<size_t>& parents,
                             const std::vector<size_t>& permut) {
  std::vector<size_t> dist_from_root(parents.size(), kEmptyValue);
  std::vector<size_t> dist_from_parent(parents.size(), kEmptyValue);

  if (parents[permut[0]] != permut[0]) {
    // starting not from root -> impossible
    dist_from_parent.clear();
    return dist_from_parent;
  }
  dist_from_parent[permut[0]] = 0;
  dist_from_root[permut[0]] = 0;

  for (size_t i = 1; i < permut.size(); ++i) {
    size_t parent_dist = dist_from_root[parents[permut[i]]];
    if (parent_dist == kEmptyValue) {
      dist_from_parent.clear();
      break;
    }
    dist_from_root[permut[i]] = dist_from_root[permut[i - 1]] + 1;
    dist_from_parent[permut[i]] = dist_from_root[permut[i]] - parent_dist;
  }

  return dist_from_parent;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
5
3 1 3 3 1
3 1 2 5 4
3
1 1 2
3 1 2
7
1 1 2 3 4 5 6
1 2 3 4 5 6 7
6
4 4 4 4 1 1
4 2 1 5 6 3
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
