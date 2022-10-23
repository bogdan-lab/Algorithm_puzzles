#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

struct Extremum {
  int index = 0;
  int64_t value = 0;
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
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  if (data.size() == 1) {
    std::cout << "1 1 " << data.front() << '\n';
    return;
  }

  std::vector<int64_t> prefix(data.size() + 1);
  for (int i = 1; i < prefix.size(); ++i) {
    prefix[i] = prefix[i - 1] + data[i - 1];
  }

  std::vector<Extremum> prefix_min(prefix.size());
  for (int i = 1; i < prefix.size(); ++i) {
    if (prefix_min[i - 1].value <= prefix[i]) {
      prefix_min[i] = prefix_min[i - 1];
    } else {
      prefix_min[i].index = i;
      prefix_min[i].value = prefix[i];
    }
  }

  std::vector<Extremum> suffix_max(prefix.size());
  suffix_max.back().index = prefix.size() - 1;
  suffix_max.back().value = prefix.back();
  for (int i = prefix.size() - 2; i >= 0; --i) {
    if (suffix_max[i + 1].value >= prefix[i]) {
      suffix_max[i] = suffix_max[i + 1];
    } else {
      suffix_max[i].index = i;
      suffix_max[i].value = prefix[i];
    }
  }

  int64_t max_val = std::numeric_limits<int64_t>::min();
  int start = 0;
  int end = 0;
  for (int i = 0; i < prefix.size(); ++i) {
    int curr_val = suffix_max[i].value - prefix_min[i].value;
    if (curr_val > max_val) {
      max_val = curr_val;
      start = prefix_min[i].index;
      end = suffix_max[i].index;
    }
  }

  std::cout << start + 1 << " " << end << " " << max_val << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(1
1
)";
    Solution(ss);
    std::cout << "expected = 1 1 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
-1 2
)";
    Solution(ss);
    std::cout << "expected = 2 2 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
-1 2 3 -2 5
)";
    Solution(ss);
    std::cout << "expected = 2 5 8\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
1 -1 -3 -2 -6
)";
    Solution(ss);
    std::cout << "expected = 1 1 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
100 -50
)";
    Solution(ss);
    std::cout << "expected = 1 1 100\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
5 -10 5
)";
    Solution(ss);
    std::cout << "expected = 1 1 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
5 -4 5
)";
    Solution(ss);
    std::cout << "expected = 1 3 6\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
5 5 5
)";
    Solution(ss);
    std::cout << "expected = 1 3 15\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
-5 5 -5
)";
    Solution(ss);
    std::cout << "expected = 2 2 5\n";
  }
}
