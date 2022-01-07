#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
int GetMaxLength(const std::vector<int>& data);
std::vector<int> GetSuffixLength(const std::vector<int>& data);
std::vector<int> GetPrefixLength(const std::vector<int>& data);

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
  std::cout << GetMaxLength(data) << '\n';
}

std::vector<int> GetSuffixLength(const std::vector<int>& data) {
  std::vector<int> result(data.size(), 0);
  int curr_len = 1;
  result.back() = curr_len;
  for (int i = data.size() - 2; i >= 0; --i) {
    if (data[i + 1] > data[i]) {
      curr_len += 1;
    } else {
      curr_len = 1;
    }
    result[i] = curr_len;
  }
  return result;
}

std::vector<int> GetPrefixLength(const std::vector<int>& data) {
  std::vector<int> result(data.size(), 0);
  int curr_len = 0;
  for (int i = 0; i < result.size(); ++i) {
    result[i] = curr_len;
    if (i == 0 || data[i] > data[i - 1]) {
      curr_len++;
    } else {
      curr_len = 1;
    }
  }
  return result;
}

int GetMaxLength(const std::vector<int>& data) {
  std::vector<int> sufix_length = GetSuffixLength(data);
  std::vector<int> prefix_length = GetPrefixLength(data);
  std::vector<int> possible_ans;
  possible_ans.reserve(data.size());
  for (int i = 0; i < data.size() - 1; ++i) {
    int pure = sufix_length[i];
    int changed = std::max(prefix_length[i] + 1, 1 + sufix_length[i + 1]);
    if (i == 0 || data[i + 1] - data[i - 1] >= 2) {
      changed = prefix_length[i] + 1 + sufix_length[i + 1];
    }
    possible_ans.push_back(std::max(pure, changed));
  }
  possible_ans.push_back(prefix_length.back() + 1);
  return *std::max_element(possible_ans.begin(), possible_ans.end());
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
7 2 3 1 5 6
)";
    Solution(ss);
    std::cout << "expected = 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
1 2 3 3 7 8
)";
    Solution(ss);
    std::cout << "expected = 6\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
1 2 3
)";
    Solution(ss);
    std::cout << "expected = 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
7 8 9 1 2 3
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
1 2 3 4 5
)";
    Solution(ss);
    std::cout << "expected = 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
1 4 3 4
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
1 2 3 1
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
7 2 3 1 4 5
)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
}
