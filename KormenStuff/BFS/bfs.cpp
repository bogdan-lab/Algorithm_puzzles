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

struct BFSNode;

using NodeColl = std::vector<BFSNode*>;

struct BFSNode {
  BFSNode* parent = nullptr;
  NodeColl childs;
  ID id;

  BFSNode(ID id_, BFSNode* p) : id(id_), parent(p) {}
};

struct BFSTree {
  BFSNode* root;
  NodeColl trace_ends;
};

BFSTree BuildBFSTree(const Maze& m) {
  NodeColl trace_ends(m.graph.size(), nullptr);
  std::vector<Color> colors(m.graph.size(), Color::WHITE);
  BFSNode* root = new BFSNode{m.start, nullptr};
  trace_ends[m.start] = root;
  colors[m.start] = Color::GRAY;
  std::queue<BFSNode*> buff;
  buff.push(root);
  while (!buff.empty()) {
    BFSNode* curr = buff.front();
    buff.pop();
    colors[curr->id] = Color::BLACK;
    for (auto id : m.graph[curr->id]) {
      if (colors[id] == Color::WHITE) {
        colors[id] = Color::GRAY;
        BFSNode* this_node = new BFSNode{id, curr};
        buff.push(this_node);
        trace_ends[id] = this_node;
        curr->childs.push_back(this_node);
      }
    }
  }
  return {root, trace_ends};
}

std::vector<ID> get_trace_vector(const BFSTree& bt, ID start, ID end) {
  if (start != bt.root->id) exit(1);
  std::vector<ID> res;
  BFSNode* curr = bt.trace_ends[end];
  res.push_back(curr->id);
  while (curr->parent) {
    res.push_back(curr->parent->id);
    curr = curr->parent;
  }
  std::reverse(res.begin(), res.end());
  return res;
}

void print_solution(std::vector<ID> trace, const Map& m, std::ostream& out) {
  std::sort(trace.begin(), trace.end());
  auto tr_it = trace.begin();
  for (const auto& vec : m.map) {
    for (auto el : vec) {
      if (el) {
        if (tr_it != trace.end() && *el == *tr_it) {
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
  std::vector<ID> trace = get_trace_vector(bt, maze.start, maze.end);
  print_solution(std::move(trace), mp, std::cout);
  return 0;
}
