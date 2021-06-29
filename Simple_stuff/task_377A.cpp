#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using ID = int;

struct Map {
  using ValType = std::vector<std::vector<std::optional<ID>>>;
  ValType m;
  ID max_id;
};

using Graph = std::vector<std::vector<ID>>;

Map read_map(std::istream& input, int line_num) {
  Map maze_map;
  maze_map.m = Map::ValType(line_num);
  ID curr_id = 0;
  int curr_line = 0;
  for (std::string buff; std::getline(input, buff);) {
    for (auto ch : buff) {
      if (ch == '#') {
        maze_map.m[curr_line].push_back(std::nullopt);
      } else {
        maze_map.m[curr_line].push_back(curr_id++);
      }
    }
    curr_line++;
  }
  maze_map.max_id = curr_id - 1;
  return maze_map;
}

Graph build_graph(const Map& maze) {
  Graph g(maze.max_id + 1);
  for (int i = 0; i < maze.m.size(); ++i) {
    for (int j = 0; j < maze.m[i].size(); ++j) {
      if (!maze.m[i][j]) continue;
      ID curr_id = *maze.m[i][j];
      if (i > 0 && maze.m[i - 1][j]) {
        g[curr_id].push_back(*maze.m[i - 1][j]);
      }
      if (i < maze.m.size() - 1 && maze.m[i + 1][j]) {
        g[curr_id].push_back(*maze.m[i + 1][j]);
      }
      if (j > 0 && maze.m[i][j - 1]) {
        g[curr_id].push_back(*maze.m[i][j - 1]);
      }
      if (i < maze.m[i].size() && maze.m[i][j + 1]) {
        g[curr_id].push_back(*maze.m[i][j + 1]);
      }
    }
  }
  return g;
}

void solution(std::istream& input = std::cin) {
  int lines, cols, walls;
  input >> lines >> cols >> walls;
  Map m = read_map(input, lines);
  Graph g = build_graph(m);
}

int main() {
  std::stringstream ss;
  ss << R"(3 4 2
#..#
..#.
#...)";
  solution(ss);

  return 0;
}
