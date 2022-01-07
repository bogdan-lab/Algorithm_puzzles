#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

struct Range {
  int last_val = 0;
  int first_val = 0;
  int length = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();
int GetMaxLength(const std::vector<int>& data);
int GetMaxLength2(const std::vector<int>& data);
std::vector<Range> GetMaxNoChangeLength(const std::vector<int>& data);

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
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }
  std::cout << GetMaxLength2(data) << '\n';
}

std::vector<Range> GetMaxNoChangeLength(const std::vector<int>& data) {
  std::vector<Range> result;
  result.reserve(data.size());
  Range rng{.last_val = data.front(), .first_val = data.front(), .length = 1};
  for (int i = 1; i < data.size(); ++i) {
    if (data[i] > data[i - 1]) {
      rng.length += 1;
    } else {
      result.push_back(rng);
      rng.length = 1;
      rng.first_val = data[i];
    }
    rng.last_val = data[i];
  }
  result.push_back(rng);
  return result;
}

int GetMaxLength2(const std::vector<int>& data) {
  std::vector<Range> no_change_length = GetMaxNoChangeLength(data);
  int max_length = no_change_length.front().length;
  for (int i = 1; i < no_change_length.size(); ++i) {
    max_length = std::max(max_length, no_change_length[i].length +
                                          no_change_length[i - 1].length);
  }
  return max_length;
}

int GetMaxLength(const std::vector<int>& data) {
  int max_length = 1;
  int curr_len = 1;
  int prev_val = data.front();
  int changed_pos = -1;
  bool can_change = true;
  for (int i = 1; i < data.size(); ++i) {
    if (data[i] > prev_val) {
      curr_len += 1;
      prev_val = data[i];
    } else {
      if (can_change) {
        can_change = false;
        curr_len += 1;
        prev_val += 1;
        changed_pos = i;
      } else {
        int new_start_pos = data[changed_pos] < data[changed_pos + 1]
                                ? changed_pos
                                : changed_pos + 1;
        curr_len = i - new_start_pos + 1;
        if (data[i] > data[i - 1]) {
          // no need to change now -> changing the first value
          curr_len += 1;
          prev_val = data[i];
        } else {
          prev_val += 1;
          changed_pos = i;
        }
      }
    }
    max_length = std::max(max_length, curr_len);
  }
  return max_length;
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
}
