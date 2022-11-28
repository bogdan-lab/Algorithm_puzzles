#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int GetNumForPath(const std::vector<int>& data, const std::vector<int>& potion,
                  int64_t power) {
  int i = 0;
  int p = 0;
  while (i < data.size()) {
    if (data[i] < power) {
      power += data[i] / 2;
      ++i;
    } else {
      if (p < potion.size()) {
        power *= potion[p];
        ++p;
      } else {
        break;
      }
    }
  }
  return i;
}

int GetCosmNum(std::vector<int>& data, int64_t power) {
  std::sort(data.begin(), data.end());
  int num = 0;
  std::vector<int> potion = {2, 2, 3};
  for (int i = 0; i < 3; ++i) {
    num = std::max(num, GetNumForPath(data, potion, power));
    std::rotate(potion.begin(), potion.begin() + 1, potion.end());
  }
  return num;
}

void Solution(std::istream& input) {
  int t;
  input >> t;

  while (t--) {
    int n;
    int64_t power;
    input >> n >> power;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::cout << GetCosmNum(data, power) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(8
4 1
2 1 8 9
3 3
6 2 60
4 5
5 1 100 5
3 2
38 6 3
1 1
12
4 6
12 12 36 100
4 1
2 1 1 15
3 5
15 1 13
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
