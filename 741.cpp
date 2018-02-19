#include <vector>
#include <iostream>

class Solution {
public:
  int cherryPickup(std::vector<std::vector<int>>& grid) {
    int n = grid.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n));
    dp[0][0] = 0;
    for (int k = 0, k1 = n + n - 1; k < k1; ++k) {
      for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
          int i1 = k  - i, j1 = k - j;
          if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= n || grid[i][i1] < 0 || grid[j][j1] < 0) {
            dp[i][j] = -1;
            continue;
          }
          if (i) {
            dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
          }
          if (j) {
            dp[i][j] = std::max(dp[i][j], dp[i][j - 1]);
          }
          if (i && j) {
            dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1]);
          }
          if (dp[i][j] >= 0) {
            dp[i][j] += (i == j ? grid[i][i1] : grid[i][i1] + grid[j][j1]);
          }
          std::cout << k << ' ' << i << ' ' << j << std::endl;
        }
      }
      /*
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          std::cout << dp[i][j] << ' ';
        }
        std::cout << std::endl;
      }
      */
    }
    return std::max(dp[n - 1][n - 1], 0);
  }
};
