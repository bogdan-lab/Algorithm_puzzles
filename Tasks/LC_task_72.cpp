#include <algorithm>
#include <string>
#include <vector>

class Solution {
 public:
  int minDistance(std::string word1, std::string word2) {
    std::vector<std::vector<int>> dp(word1.size() + 1,
                                     std::vector<int>(word2.size() + 1));
    for (int i = 0; i < dp.size(); ++i) {
      dp[i][0] = i;
    }
    for (int i = 0; i < dp[0].size(); ++i) {
      dp[0][i] = i;
    }

    for (int i = 0; i < word1.size(); ++i) {
      for (int j = 0; j < word2.size(); ++j) {
        if (word1[i] == word2[j]) {
          dp[i + 1][j + 1] = dp[i][j];
        } else {
          dp[i + 1][j + 1] =
              std::min({dp[i][j] + 1, dp[i][j + 1] + 1, dp[i + 1][j] + 1});
        }
      }
    }

    return dp[word1.size()][word2.size()];
  }
};
