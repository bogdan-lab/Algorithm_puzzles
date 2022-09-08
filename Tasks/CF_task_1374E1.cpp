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
  int book_num, like_num;
  input >> book_num >> like_num;

  std::vector<int> both;
  std::vector<int> alice;
  std::vector<int> bob;
  int t, a, b;
  while (book_num--) {
    input >> t >> a >> b;
    if (a && b) {
      both.push_back(t);
    } else if (a) {
      alice.push_back(t);
    } else if (b) {
      bob.push_back(t);
    }
  }
  std::sort(alice.begin(), alice.end());
  std::sort(bob.begin(), bob.end());

  auto ait = alice.begin();
  auto bit = bob.begin();
  while (ait != alice.end() && bit != bob.end()) {
    both.push_back(*ait + *bit);
    ++ait;
    ++bit;
  }

  std::sort(both.begin(), both.end());

  if (both.size() < like_num) {
    std::cout << "-1\n";
    return;
  }

  int total_time = 0;
  for (int i = 0; i < like_num; ++i) {
    total_time += both[i];
  }
  std::cout << total_time << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(8 4
7 1 1
2 1 1
4 0 1
8 1 1
1 0 1
1 1 1
1 0 1
3 0 0
)";
    Solution(ss);
    std::cout << "expected = 18\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 2
6 0 0
9 0 0
1 0 1
2 1 1
5 1 0
)";
    Solution(ss);
    std::cout << "expected = 8\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 3
3 0 0
2 1 0
3 1 0
5 0 1
3 0 1
)";
    Solution(ss);
    std::cout << "expected = -1\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 2
1 1 0
3 1 0
1 0 1
3 0 1
5 1 1)";
    Solution(ss);
    std::cout << "expected = 7\n";
  }
}
