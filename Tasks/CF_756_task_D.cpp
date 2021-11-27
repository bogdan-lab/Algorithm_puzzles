#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
std::vector<size_t> SolveOne(const std::vector<size_t>& parents,
                             const std::vector<size_t>& permut);

std::vector<std::unordered_set<size_t>> ParentsToChild(
    const std::vector<size_t>& parents);

bool CheckIfPossible(
    const std::vector<size_t>& permut,
    const std::vector<std::unordered_set<size_t>>& par_to_child);

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
  std::vector<size_t> dist_from_root(parents.size());
  std::vector<size_t> dist_from_parent(parents.size());
  std::vector<std::unordered_set<size_t>> parent_to_child =
      ParentsToChild(parents);
  if (!CheckIfPossible(permut, parent_to_child)) {
    dist_from_parent.clear();
    return dist_from_parent;
  }

  size_t curr_val = 1;
  for (size_t i = 1; i < permut.size(); ++i) {
    dist_from_root[permut[i]] += curr_val;
    dist_from_parent[permut[i]] = curr_val;
    size_t tmp_val = std::max(dist_from_root[permut[i]], curr_val);
    for (size_t child = 0; child < parents.size(); ++child) {
      if (parent_to_child[permut[i]].count(child)) {
        dist_from_root[child] += curr_val;
      }
    }
    curr_val = tmp_val + 1;
  }

  return dist_from_parent;
}

std::vector<std::unordered_set<size_t>> ParentsToChild(
    const std::vector<size_t>& parents) {
  std::vector<std::unordered_set<size_t>> result(parents.size());

  for (size_t i = 0; i < parents.size(); ++i) {
    if (parents[i] == i) continue;
    result[parents[i]].insert(i);
    size_t j = parents[i];
    while (parents[j] != j) {
      result[parents[j]].insert(i);
      j = parents[j];
    }
  }

  return result;
}

bool CheckIfPossible(
    const std::vector<size_t>& permut,
    const std::vector<std::unordered_set<size_t>>& par_to_child) {
  auto is_child = [&](size_t test_child, size_t test_parent) {
    return par_to_child[test_parent].count(test_child);
  };
  for (size_t i = 0; i < permut.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (is_child(permut[j], permut[i])) {
        return false;
      }
    }
  }
  return true;
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
