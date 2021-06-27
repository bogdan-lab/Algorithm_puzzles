#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using ID = int;
using Graph = std::vector<std::vector<ID>>;

struct Point {
  int x;
  int y;
};

struct StartEnd {
  std::optional<ID> start;
  std::optional<ID> end;
};

struct Map {
  std::vector<std::vector<std::optional<ID>>> map;
  StartEnd start_end;
  ID max_id;
};

struct Maze {
  Graph graph;
  ID start;
  ID end;
};

Map get_map_from_file(const char* fname) {
  std::ifstream input{fname};
  ID curr_id = 0;
  Map m;
  std::string buff;
  while (std::getline(input, buff)) {
    std::vector<std::optional<ID>> map_buff;
    map_buff.reserve(buff.size());
    for (int col = 0; col < buff.size(); ++col) {
      switch (buff[col]) {
        case 'X': {
          map_buff.push_back(std::nullopt);
          break;
        }
        case '.':
          if (!m.start_end.start) {
            m.start_end.start = curr_id;
          } else if (!m.start_end.end) {
            m.start_end.end = curr_id;
          }
        case ' ': {
          map_buff.push_back(curr_id++);
          break;
        }
        default:
          exit(1);
      }
    }
    m.map.push_back(std::move(map_buff));
  }
  m.max_id = curr_id - 1;
  return m;
}

Maze construct_maze(const Map& m) {
  Maze maze;
  maze.start = m.start_end.start.value();
  maze.end = m.start_end.end.value();
  maze.graph = Graph(m.max_id + 1);
  for (int line = 0; line < m.map.size(); ++line) {
    for (int col = 0; col < m.map[line].size(); ++col) {
      if (!m.map[line][col]) continue;
      ID id = m.map[line][col].value();
      if (col > 0 && m.map[line][col - 1]) {
        maze.graph[id].push_back(m.map[line][col - 1].value());
      }
      if (col < m.map[line].size() - 1 && m.map[line][col + 1]) {
        maze.graph[id].push_back(m.map[line][col + 1].value());
      }
      if (line > 0 && m.map[line - 1][col]) {
        maze.graph[id].push_back(m.map[line - 1][col].value());
      }
      if (line < m.map.size() - 1 && m.map[line + 1][col]) {
        maze.graph[id].push_back(m.map[line + 1][col].value());
      }
    }
  }
  return maze;
}

enum class Color { WHITE, GRAY, BLACK };

struct BFSTree {
  std::vector<Color> colors;
  Graph traces;
  ID start;
  ID end;
};

BFSTree BuildBFSTree(const Maze& m) {
  BFSTree bt;
  bt.start = m.start;
  bt.end = m.end;
  bt.colors = std::vector<Color>(m.graph.size(), Color::WHITE);
  bt.traces = Graph(m.graph.size());
  ID curr = bt.start;
  std::queue<ID> buff;
  buff.push(bt.start);
  bt.colors[bt.start] = Color::GRAY;
  bt.traces[bt.start].push_back(bt.start);
  while (!buff.empty()) {
    ID curr = buff.front();
    bt.colors[curr] = Color::BLACK;
    buff.pop();
    for (auto id : m.graph[curr]) {
      if (bt.colors[id] == Color::WHITE) {
        buff.push(id);
        bt.colors[id] = Color::GRAY;
        bt.traces[id].assign(bt.traces[curr].begin(), bt.traces[curr].end());
        bt.traces[id].push_back(id);
      }
    }
  }
  return bt;
}

void print_solution(const std::vector<ID>& trace, const Map& m,
                    std::ostream& out) {
  auto s_trace = trace;
  std::sort(s_trace.begin(), s_trace.end());
  auto tr_it = s_trace.begin();
  for (const auto& vec : m.map) {
    for (auto el : vec) {
      if (el) {
        if (tr_it != s_trace.end() && *el == *tr_it) {
          out << '.';
          ++tr_it;
        } else {
          out << ' ';
        }
      } else {
        out << 'X';
      }
    }
    out << '\n';
  }
}

int main() {
  Map mp = get_map_from_file("maze_test_1");
  Maze maze = construct_maze(mp);
  BFSTree bt = BuildBFSTree(maze);
  print_solution(bt.traces[bt.end], mp, std::cout);
  return 0;
}
