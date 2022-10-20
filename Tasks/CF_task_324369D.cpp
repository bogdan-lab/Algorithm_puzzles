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

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }

    int64_t count = 0;
    int start =
        std::find_if(data.begin(), data.end(), [](int v) { return v > 1; }) -
        data.begin();
    while (start < data.size()) {
      int next = start;
      while (next < data.size()) {
        if (data[next] == 1) {
          ++next;
        } else {
          --data[next];
          next += data[next] + 1;
        }
      }
      ++count;
      if (data[start] == 1) {
        start = std::find_if(data.begin() + start, data.end(),
                             [](int v) { return v > 1; }) -
                data.begin();
      }
    }

    std::cout << count << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
7
1 4 2 2 2 2 2
2
2 3
5
1 1 1 1 1
)";
    Solution(ss);
    std::cout << "expected = 4; 3; 0\n";
  }
}
