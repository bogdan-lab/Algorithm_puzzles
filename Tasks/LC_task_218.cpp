#include <stack>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> getSkyline(
      std::vector<std::vector<int>>& buildings) {
    std::vector<std::vector<int>> res;

    std::stack<std::vector<int>> buff;
    std::stack<std::vector<int>> buff2;
    int i = 0;
    while (i < buildings.size()) {
      int left = buildings[i][0];
      // TODO pop all in the past
      while (left == buildings[i][0]) {
        if (buff.empty()) {
          buff.push(buildings[i]);
        } else if (buff.top()[2] < buildings[i][2]) {
          if (buff.top()[1] <= buildings[i][1]) {
            buff.pop();
          }
          buff.push(buildings[i]);
        } else if (buff.top()[2] > buildings[i][2] &&
                   buildings[i][1] > buff.top()[1]) {
          while (!buff.empty() && buildings[i][1] > buff.top()[1] &&
                 buildings[i][2] < buff.top()[2]) {
            buff2.push(buff.top());
            buff.pop();
          }
          // check why we stopped
          if (buff.empty()) {
            buff.push(buildings[i]);
          } else if (buildings[i][1] <= buff.top()[1]) {
            if (buildings[i][2] > buff.top()[2]) {
              if (buildings[i][1] == buff.top()[1]) {
                buff.pop();
              }
              buff.push(buildings[i]);
            }
          } else {
            // buildings[i][2] >= buff.top()[2]
            if (buildings[i][2] == buff.top()[2]) {
              if (buildings[i][1] > buff.top()[1]) {
                buff.pop();
                buff.push(buildings[i]);
              }
            } else {
              if (!buff.empty() && buildings[i][1] >= buff.top()[1]) {
                buff.pop();
              }
              buff.push(buildings[i]);
            }
          }

          if (buff.empty() || !(buildings[i][1] <= buff.top()[1] &&
                                buildings[i][2] < buff.top()[2])) {
          }
        }
        buff.push(buildings[i]);
        ++i;
      }

      res.push_back({left, buff.top()[2]});
      ++i;
    }

    return res;
  }
};
