#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr int kMaxValue = 100'000;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Print(bool check) { std::cout << (check ? "Yes\n" : "No\n"); }

bool CheckConstruction(int fourth, int twos) {
  if (fourth >= 2) {
    return true;
  }
  if (fourth == 1 && twos > 3) {
    return true;
  }
  return false;
}

bool ProcessAdd(std::vector<int>& count, int& fourth, int& twos, int val) {
  int prev_4 = count[val] / 4;
  int prev_2 = count[val] / 2;
  ++count[val];
  int curr_4 = count[val] / 4;
  int curr_2 = count[val] / 2;

  if (prev_4 < curr_4) {
    ++fourth;
  }
  if (prev_2 < curr_2) {
    ++twos;
  }
  return CheckConstruction(fourth, twos);
}

bool ProcessSubtract(std::vector<int>& count, int& fourth, int& twos, int val) {
  int prev_4 = count[val] / 4;
  int prev_2 = count[val] / 2;
  --count[val];
  int curr_4 = count[val] / 4;
  int curr_2 = count[val] / 2;

  if (prev_4 > curr_4) {
    --fourth;
  }
  if (prev_2 > curr_2) {
    --twos;
  }
  return CheckConstruction(fourth, twos);
}

int CountNum(const std::vector<int>& count, int num) {
  int res = 0;
  for (const auto& el : count) {
    res += el / num;
  }
  return res;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> count(kMaxValue + 1);
  while (n--) {
    int val;
    input >> val;
    ++count[val];
  }

  int fourth = CountNum(count, 4);
  int twos = CountNum(count, 2);

  int q;
  input >> q;
  while (q--) {
    std::string command;
    int val;
    input >> command >> val;
    if (command == "+") {
      Print(ProcessAdd(count, fourth, twos, val));
    } else {
      Print(ProcessSubtract(count, fourth, twos, val));
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
1 1 1 2 1 1
6
+ 2
+ 1
- 1
+ 2
- 1
+ 2
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
