#include <algorithm>
#include <vector>

class Solution {
 public:
  int calculateMinimumHP(std::vector<std::vector<int>>& dungeon) {
    int rows = dungeon.size();
    int cols = dungeon[0].size();

    dungeon[rows - 1][cols - 1] =
        dungeon[rows - 1][cols - 1] >= 0 ? 1 : 1 - dungeon[rows - 1][cols - 1];

    for (int i = rows - 2; i >= 0; --i) {
      dungeon[i][cols - 1] =
          std::max(dungeon[i + 1][cols - 1] - dungeon[i][cols - 1], 1);
    }
    for (int i = cols - 2; i >= 0; --i) {
      dungeon[rows - 1][i] =
          std::max(dungeon[rows - 1][i + 1] - dungeon[rows - 1][i], 1);
    }

    for (int i = rows - 2; i >= 0; --i) {
      for (int j = cols - 2; j >= 0; --j) {
        dungeon[i][j] =
            std::max(1, std::min(dungeon[i + 1][j] - dungeon[i][j],
                                 dungeon[i][j + 1] - dungeon[i][j]));
      }
    }

    return dungeon.front().front();
  }
};
