#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
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
  std::vector<std::string> desk(8);
  while (t--) {
    for (auto& el : desk) {
      input >> el;
    }

    auto begin =
        std::find_if(desk.begin(), desk.end(), [](const std::string& str) {
          size_t count = std::count(str.begin(), str.end(), '#');
          return count == 2;
        });
    auto res = std::find_if(begin, desk.end(), [](const std::string& str) {
      size_t count = std::count(str.begin(), str.end(), '#');
      return count == 1;
    });
    int row = res - desk.begin();
    int col = res->find('#');
    std::cout << row + 1 << ' ' << col + 1 << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3

.....#..
#...#...
.#.#....
..#.....
.#.#....
#...#...
.....#..
......#.

#.#.....
.#......
#.#.....
...#....
....#...
.....#..
......#.
.......#

.#.....#
..#...#.
...#.#..
....#...
...#.#..
..#...#.
.#.....#
#.......
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
