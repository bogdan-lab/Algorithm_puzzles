#include <algorithm>
#include <iostream>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using ID = int;

struct Map {
  using ValType = std::vector<std::vector<std::optional<ID>>>;
  ValType m;
  ID max_id;
};

using Graph = std::vector<std::vector<ID>>;

struct DFSnode {
  int t_in;
  int t_out;
  ID id;
};

enum class Colors { WHITE, GRAY, BLACK };

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

std::vector<DFSnode> do_DFS(const Graph& g) {
  std::vector<DFSnode> nds(g.size());
  std::vector<Colors> colors(g.size(), Colors::WHITE);
  int timestamp = 0;
  std::stack<ID> buff;
  buff.push(0);
  colors[0] = Colors::GRAY;
  nds[0].t_in = timestamp++;
  nds[0].id = 0;
  while (!buff.empty()) {
    ID top_id = buff.top();
    auto it = std::find_if(g[top_id].begin(), g[top_id].end(), [&](ID ch_id) {
      return colors[ch_id] == Colors::WHITE;
    });
    if (it == g[top_id].end()) {
      nds[top_id].t_out = timestamp++;
      colors[top_id] = Colors::BLACK;
      buff.pop();
    } else {
      nds[*it].t_in = timestamp++;
      nds[*it].id = *it;
      colors[*it] = Colors::GRAY;
      buff.push(*it);
    }
  }
  return nds;
}

std::vector<ID> get_new_walls_ids(std::vector<DFSnode> time_vec, int wall_num) {
  std::vector<DFSnode> op_vec = std::move(time_vec);
  auto srt_end = op_vec.begin() + wall_num;
  std::partial_sort(op_vec.begin(), srt_end, op_vec.end(),
                    [](const DFSnode& lhs, const DFSnode rhs) {
                      return lhs.t_out - lhs.t_in < rhs.t_out - rhs.t_in;
                    });
  std::sort(
      op_vec.begin(), srt_end,
      [](const DFSnode& lhs, const DFSnode& rhs) { return lhs.id < rhs.id; });
  std::vector<ID> res;
  res.reserve(wall_num);
  for(auto it=op_vec.begin(); it!=srt_end; ++it){
      res.push_back(it->id);
  }
  return res;
}

void solution(std::istream& input = std::cin) {
  int lines, cols, walls;
  input >> lines >> cols >> walls;
  Map m = read_map(input, lines);
  // here print if walls = 0!;
  Graph g = build_graph(m);
  std::vector<DFSnode> time_vec = do_DFS(g);
  std::vector<ID> wall_vec = get_new_walls_ids(time_vec, walls);
  //here print result with wall_vec
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
