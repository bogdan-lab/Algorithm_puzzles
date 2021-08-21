#include <iostream>
#include <queue>
#include <sstream>
#include <string>

void solution(std::istream& input = std::cin);
void run_tests();
std::string fill_array(int len);
std::string get_vec_string(const std::vector<int>& vec);

struct Interval {
  int start = 0;
  int end = 0;

  bool operator<(const Interval& rhs) const {
    int len = end - start;
    int rhs_len = rhs.end - rhs.start;
    return len < rhs_len || (len == rhs_len && start > rhs.start);
  }
};

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

std::string get_vec_string(const std::vector<int>& vec) {
  std::stringstream ss;
  for (auto el : vec) {
    ss << el << ' ';
  }
  return ss.str();
}

std::string fill_array(int n) {
  std::vector<int> vec(n, 0);
  std::priority_queue<Interval> queue;
  queue.push(Interval{1, n});
  int iter = 1;
  while (!queue.empty()) {
    Interval top = queue.top();
    queue.pop();
    int len = top.end - top.start + 1;
    int midpoint =
        len % 2 ? (top.start + top.end) / 2 : (top.start + top.end - 1) / 2;
    vec[midpoint - 1] = iter;
    if (midpoint < top.end) {
      queue.push(Interval{midpoint + 1, top.end});
    }
    if (midpoint > top.start) {
      queue.push(Interval{top.start, midpoint - 1});
    }
    ++iter;
  }
  return get_vec_string(vec);
}

void solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) {
    int len;
    input >> len;
    std::cout << fill_array(len) << '\n';
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(
6
1
2
3
4
5
6
        )";
    solution(ss);
    std::cout << "expected\n";
    std::cout << "1\n";
    std::cout << "1 2\n";
    std::cout << "2 1 3\n";
    std::cout << "3 1 2 4\n";
    std::cout << "2 4 1 3 5\n";
    std::cout << "3 4 1 5 2 6\n";
  }
}
