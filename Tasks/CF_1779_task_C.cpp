#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //RunTests();
   Solution(std::cin);
  return 0;
}

void SolveOne(std::istream& input) {
  int n, m;
  input >> n >> m;
  --m;
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }


  int count = 0;
  int64_t s = 0;
  std::priority_queue<int64_t, std::vector<int64_t>, std::less<int64_t>>
      max_queue;
  for (int i = m; i > 0; --i) {
    s += data[i];
    if (data[i] > 0) {
      max_queue.push(data[i]);
    }
    if (s > 0) {
      s -= 2LL * max_queue.top();
      max_queue.pop();
      ++count;
    }
  }

  s = 0;
  std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>>
      min_queue;
  for (int i = m + 1; i < data.size(); ++i) {
    s += data[i];
    if (data[i] < 0) {
      min_queue.push(data[i]);
    }
    if (s < 0) {
      ++count;
      s -= 2LL * min_queue.top();
      min_queue.pop();
    }
  }

  std::cout << count << '\n';
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
14 2
3 5 10 -6 -2 -3 -1 -1 -1 -1 -1 -1 -1 -1
14 2
3 -5 10 6 -2 -3 -1 -1 -1 -1 -1 -1 -1 -1
)";
    Solution(ss);
    std::cout << "expected = 2; 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(6
4 3
-1 -2 -3 -4
4 3
1 2 3 4
1 1
1
5 5
-2 3 -5 1 -20
5 2
-2 3 -5 -5 -20
10 4
345875723 -48 384678321 -375635768 -35867853 -35863586 -358683842 -81725678 38576 -357865873
)";
    Solution(ss);
    std::cout << "expected = 1; 1; 0; 0; 3; 4\n";
  }
}
