#include <vector>

class Solution {
public:
  int uniquePathsWithObstacles(std::vector<std::vector<int>> &obstacleGrid) {
    int n = obstacleGrid.size();
    int m = n ? obstacleGrid[0].size() : 0;
    if (!m) {
      return 0;
    }
    std::vector<int> dp(m);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
      if (obstacleGrid[i][0]) {
        dp[0] = 0;
      }
      for (int j = 1; j < m; ++j) {
        if (obstacleGrid[i][j]) {
          dp[j] = 0;
        } else {
          dp[j] += dp[j - 1];
        }
      }
    }
    return dp[m - 1];
  }
};
