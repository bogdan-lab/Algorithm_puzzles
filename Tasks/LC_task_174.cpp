#include <algorithm>
#include <vector>

struct Path {
  int agg = 0;
  int min_drop = 0;
};

class Solution {
 public:
  int calculateMinimumHP(std::vector<std::vector<int>>& dungeon) {
    std::vector<std::vector<Path>> data(dungeon.size(),
                                        std::vector<Path>(dungeon[0].size()));

    data[0][0].agg = dungeon[0][0];
    data[0][0].min_drop = dungeon[0][0];
    for (int i = 1; i < dungeon[0].size(); ++i) {
      data[0][i].agg = data[0][i - 1].agg + dungeon[0][i];
      data[0][i].min_drop = std::min(data[0][i - 1].min_drop, data[0][i].agg);
    }

    for (int i = 1; i < dungeon.size(); ++i) {
      data[i][0].agg = data[i - 1][0].agg + dungeon[i][0];
      data[i][0].min_drop = std::min(data[i - 1][0].min_drop, data[i][0].agg);
    }

    for (int i = 1; i < dungeon.size(); ++i) {
      for (int j = 1; j < dungeon[0].size(); ++j) {
        int top_agg = data[i - 1][j].agg + dungeon[i][j];
        int from_top = std::min(top_agg, data[i - 1][j].min_drop);
        int right_agg = data[i][j - 1].agg + dungeon[i][j];
        int from_right = std::min(right_agg, data[i][j - 1].min_drop);
        if (right_agg > top_agg ||
            (right_agg == top_agg && from_right > from_top)) {
          data[i][j].min_drop = from_right;
          data[i][j].agg = right_agg;
        } else {
          data[i][j].min_drop = from_top;
          data[i][j].agg = top_agg;
        }
      }
    }

    int min_drop = data.back().back().min_drop;
    return min_drop >= 0 ? 1 : 1 - min_drop;
  }
};
