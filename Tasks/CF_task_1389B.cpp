#include <iostream>
#include <sstream>
#include <vector>

struct Step {
  int prev_index;
  int curr_index;
};

void Solution(std::istream& input = std::cin);
void RunTests();
int CalcMaxScore(const std::vector<int>& data, int max_steps, int max_left);

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
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::cout << CalcMaxScore(data, max_steps, max_left) << '\n';
  }
}

int CalcMaxScore(const std::vector<int>& data, int max_steps, int max_left) {
  int count = data[0];
  int prev_pos = 0;
  int curr_pos = 0;
  while (max_steps--) {
    if (prev_pos < curr_pos && curr_pos > 0 && max_left > 0 &&
        data[curr_pos - 1] > data[curr_pos + 1]) {
      max_left--;
      prev_pos = curr_pos;
      curr_pos -= 1;
    } else {
      prev_pos = curr_pos;
      curr_pos += 1;
    }
    count += data[curr_pos];
  }
  return count;
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
