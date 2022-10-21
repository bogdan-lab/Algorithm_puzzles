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
    int start = 0;
    while (true) {
      start = std::find_if(data.begin() + start, data.end(),
                           [](int v) { return v > 1; }) -
              data.begin();
      if (start == data.size()) break;
      if (data[start] + start >= data.size()) {
        int new_val = std::max<int>(data.size() - 1 - start, 1);
        count += data[start] - new_val;
        data[start] = new_val;
      } else {
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
      }
    }

    std::cout << count << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
7
1 4 2 2 2 2 2
2
2 3
5
1 1 1 1 1
4
1 9 2 1
)";
    Solution(ss);
    std::cout << "expected = 4; 3; 0; 9\n";
  }
}
