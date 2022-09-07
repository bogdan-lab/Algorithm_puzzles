#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Position {
  int x = 0;
  int y = 0;
};

bool operator==(const Position& lhs, const Position& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Position& lhs, const Position& rhs) {
  return !(lhs == rhs);
}

std::string MoveAll(std::vector<Position>& start,
                    const std::vector<Position>& end, int x_max, int y_max);

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
  int x_max, y_max, k;
  input >> x_max >> y_max >> k;
  std::vector<Position> start(k);
  for (auto& el : start) {
    input >> el.x >> el.y;
  }
  std::vector<Position> finish(k);
  for (auto& el : finish) {
    input >> el.x >> el.y;
  }

  std::string operations = MoveAll(start, finish, x_max, y_max);
  std::cout << operations.size() << '\n' << operations << '\n';
}

std::string MoveAll(std::vector<Position>& start,
                    const std::vector<Position>& finish, int x_max, int y_max) {
  std::string operations;
  std::vector<int> chip_reached(start.size());
  int not_reached_count = start.size();
  for (int i = 0; i < start.size(); ++i) {
    if (start[i] == finish[i]) {
      chip_reached[i] = 1;
      --not_reached_count;
    }
  }
  if (!not_reached_count) return operations;

  operations.reserve(2 * x_max * y_max);
  for (int i = 0; i < x_max - 1; ++i) {
    operations.push_back('U');
    for (int i = 0; i < start.size(); ++i) {
      start[i].x = std::max(1, start[i].x - 1);
      if (start[i] == finish[i] && !chip_reached[i]) {
        chip_reached[i] = 1;
        --not_reached_count;
        if (!not_reached_count) {
          return operations;
        }
      }
    }
  }
  for (int i = 0; i < y_max - 1; ++i) {
    operations.push_back('L');
    for (int i = 0; i < start.size(); ++i) {
      start[i].y = std::max(1, start[i].y - 1);
      if (start[i] == finish[i] && !not_reached_count) {
        chip_reached[i] = 1;
        --not_reached_count;
        if (!not_reached_count) {
          return operations;
        }
      }
    }
  }

  std::vector<std::vector<int>> finish_2d(x_max + 1,
                                          std::vector<int>(y_max + 1, -1));
  for (int i = 0; i < finish.size(); ++i) {
    if (!chip_reached[i]) {
      finish_2d[finish[i].x][finish[i].y] = i;
    }
  }

  Position curr = start.front();
  bool move_up = false;
  while (curr.y <= y_max) {
    if (finish_2d[curr.x][curr.y] >= 0 &&
        !chip_reached[finish_2d[curr.x][curr.y]]) {
      chip_reached[finish_2d[curr.x][curr.y]] = 1;
      --not_reached_count;
      if (!not_reached_count) {
        return operations;
      }
    }

    if (!move_up) {
      if (curr.x == x_max) {
        operations.push_back('R');
        move_up = true;
        ++curr.y;
      } else {
        operations.push_back('D');
        ++curr.x;
      }
    } else {
      if (curr.x == 1) {
        operations.push_back('R');
        move_up = false;
        ++curr.y;
      } else {
        operations.push_back('U');
        --curr.x;
      }
    }
  }
  return operations;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 3 2
1 2
2 1
3 3
3 2
)";
    Solution(ss);
    std::cout << "expected = 3; DRD\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 4 3
3 4
3 1
3 3
5 3
1 3
1 4
)";
    Solution(ss);
    std::cout << "expected = 9; DDLUUUURR \n";
  }
}
