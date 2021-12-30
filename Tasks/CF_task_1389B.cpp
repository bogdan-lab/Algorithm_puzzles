#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <vector>

constexpr int kEmptyValue = std::numeric_limits<int>::min();
using Data = std::vector<std::vector<std::vector<int>>>;

void Solution(std::istream& input = std::cin);
void RunTests();
int CalcMaxScore(int curr_pos, int max_steps, int max_left, bool can_step_left,
                 Data& data, const std::vector<int>& array);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    int max_steps;
    int max_left;
    input >> n >> max_steps >> max_left;
    std::vector<int> array(n);
    for (auto& el : array) {
      input >> el;
    }
    Data data(array.size());
    for (auto& el : data) {
      el.resize(max_steps + 1);
      for (auto& inner_el : el) {
        inner_el.resize(max_left + 1, kEmptyValue);
      }
    }
    std::cout << CalcMaxScore(0, max_steps, max_left, true, data, array)
              << '\n';
  }
}

int CalcMaxScore(int curr_pos, int max_steps, int max_left, bool can_step_left,
                 Data& data, const std::vector<int>& array) {
  if (data[curr_pos][max_steps][max_left] != kEmptyValue) {
    return data[curr_pos][max_steps][max_left];
  }
  if (max_steps == 0) {
    data[curr_pos][max_steps][max_left] = array[curr_pos];
    return data[curr_pos][max_steps][max_left];
  }
  if (max_left == 0) {
    auto it = array.begin() + curr_pos;
    data[curr_pos][max_steps][max_left] = std::accumulate(
        it, it + std::min<int>(max_steps, array.size() - curr_pos), 0);
    return data[curr_pos][max_steps][max_left];
  }
  int left_step = kEmptyValue;
  if (curr_pos > 0 && max_left > 0 && can_step_left) {
    left_step = CalcMaxScore(curr_pos - 1, max_steps - 1, max_left - 1, false,
                             data, array);
  }
  int right_step = kEmptyValue;
  if (curr_pos < array.size() - 1 && max_steps > 0) {
    right_step =
        CalcMaxScore(curr_pos + 1, max_steps - 1, max_left, true, data, array);
  }
  data[curr_pos][max_steps][max_left] =
      array[curr_pos] + std::max(left_step, right_step);
  return data[curr_pos][max_steps][max_left];
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
5 4 0
1 5 4 3 2
5 4 1
1 5 4 3 2
5 4 4
10 20 30 40 50
10 7 3
4 6 8 2 9 9 7 4 10 9
)";
    Solution(ss);
    std::cout << "expected = 15; 19; 150; 56\n";
  }
}
