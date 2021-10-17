#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
std::vector<size_t> GetPath(const std::vector<size_t>& parent_relations);

int main() {
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  size_t n;
  size_t k;
  input >> n >> k;
  std::vector<int> prices(n);
  for (auto it = std::next(prices.begin()); it != std::prev(prices.end());
       ++it) {
    input >> *it;
  }
  std::vector<int> max_income(n);
  std::vector<size_t> parents(n);
  max_income[0] = prices[0];

  for (size_t i = 1; i < max_income.size(); ++i) {
    auto curr_it = max_income.begin() + i;
    auto max_el = std::max_element(curr_it - std::min(k, i), curr_it);
    parents[i] = static_cast<size_t>(max_el - max_income.begin());
    max_income[i] = *max_el + prices[i];
  }
  std::vector<size_t> path = GetPath(parents);
  std::cout << max_income.back() << '\n' << path.size() - 1 << '\n';
  for (const auto& el : path) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

std::vector<size_t> GetPath(const std::vector<size_t>& parent_relations) {
  std::vector<size_t> result;
  result.reserve(parent_relations.size());
  size_t curr_pos = parent_relations.size() - 1;
  while (curr_pos > 0) {
    result.push_back(curr_pos + 1);
    curr_pos = parent_relations[curr_pos];
  }
  result.push_back(1);
  std::reverse(result.begin(), result.end());
  return result;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5 3
2 -3 5
)";
    Solution(ss);
    std::cout << "expected = 7; 3; 1 2 4 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(10 3
-13 -2 -14 -124 -9 -6 -5 -7
)";
    Solution(ss);
    std::cout << "expected = -16; 4; 1 3 6 8 10\n";
  }
  {
    std::stringstream ss;
    ss << R"(12 5
-5 -4 -3 -2 -1 1 2 3 4 5
)";
    Solution(ss);
    std::cout << "expected = 14; 7; 1 6 7 8 9 10 11 12\n";
  }
}
