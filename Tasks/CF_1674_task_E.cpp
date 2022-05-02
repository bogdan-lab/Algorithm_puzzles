#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

int DestroyWall(int index, std::vector<int>& health);
int CalcShots(int index, std::vector<int> health);

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> health(n);
  for (auto& el : health) {
    input >> el;
  }

  int min_count = std::numeric_limits<int>::max();
  for (int i = 0; i < health.size(); ++i) {
    min_count = std::min(min_count, CalcShots(i, health));
  }
  std::cout << min_count << '\n';
}

int DestroyWall(int index, std::vector<int>& health) {
  int count = (health[index] + 1) / 2;
  health[index] -= count * 2;
  if (index < health.size() - 1) {
    health[index + 1] -= count;
  }
  if (index > 1) {
    health[index - 1] -= count;
  }
  return count;
}

int CalcShots(int index, std::vector<int> health) {
  int count = DestroyWall(index, health);
  auto st_it =
      std::find_if(health.begin(), health.end(), [](int el) { return el > 0; });
  int n_idx = st_it - health.begin();
  int min_val = *st_it;
  for (auto it = st_it; it != health.end(); ++it) {
    if (*it > 0 && *it < min_val) {
      min_val = *it;
      n_idx = it - health.begin();
    }
  }
  return count + DestroyWall(n_idx, health);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
20 10 30 10 20
)";
    Solution(ss);
    std::cout << "expected = 10\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
1 8 1
)";
    Solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
7 6 6 8 5 8
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
14 3 8 10 15 4
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
1 100 100 1
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
40 10 10
)";
    Solution(ss);
    std::cout << "expected = 7\n";
  }
}
