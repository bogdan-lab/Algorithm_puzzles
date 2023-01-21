#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

constexpr int kMaxVal = 10'000;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

struct Node {
  int cost = 0;
  int count = 0;
};

void Mark(std::vector<int>& lookup, Node n) {
  if (lookup.size() < n.cost) return;
  std::vector<int> buff;
  while (n.count) {
    for (int i = 0; i < lookup.size() - n.cost; ++i) {
      if (lookup[i]) {
        buff.push_back(i + n.cost);
      }
    }
    for (const auto& el : buff) {
      lookup[el] = 1;
    }
    --n.count;
  }
}

bool Check(std::vector<Node>& data, int target) {
  std::vector<int> lookup(kMaxVal + 1);
  lookup[0] = 1;
  for (const auto& el : data) {
    Mark(lookup, el);
  }
  return lookup[target];
}

void Solution(std::istream& input) {
  int n, x;
  input >> n >> x;
  std::vector<Node> data(n);
  for (auto& el : data) {
    input >> el.cost >> el.count;
  }

  if (Check(data, x)) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2 19
2 3
5 6
)";
    Solution(ss);
    std::cout << "expected = Yes\n";
  }
  {
    std::stringstream ss;
    ss << R"(2 18
2 3
5 6
)";
    Solution(ss);
    std::cout << "expected = No\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 1001
1 1
2 1
100 10
)";
    Solution(ss);
    std::cout << "expected = Yes\n";
  }
}
