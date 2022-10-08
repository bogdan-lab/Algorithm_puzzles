#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Fill(const std::vector<int>& tree, std::vector<int>& need_to_learn,
          int id) {
  if (need_to_learn[id]) return;
  need_to_learn[id] = 1;
  Fill(tree, need_to_learn, tree[id]);
}

int CountSkillPoints(std::vector<int>& tree, std::vector<int>& skills) {
  std::vector<int> need_to_learn(tree.size());
  need_to_learn[0] = 1;
  for (const auto& el : skills) {
    Fill(tree, need_to_learn, el);
  }

  return std::accumulate(need_to_learn.begin(), need_to_learn.end(), 0);
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;
  std::vector<int> tree(n);
  for (auto& el : tree) {
    input >> el;
  }
  std::vector<int> skills(m);
  for (auto& el : skills) {
    input >> el;
  }
  std::cout << CountSkillPoints(tree, skills) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4 1
    0 0 1 1
    2)";
    Solution(ss);
    std::cout << "expected = 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 2
    0 0 1 1
    2 3)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 4
    0 0 1 1
    0 1 2 3)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 1
    0 0 1 1
    0)";
    Solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(7 2
    0 0 0 0 1 2 3
    5 6)";
    Solution(ss);
    std::cout << "expected = 5\n";
  }
}
