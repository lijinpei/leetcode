#include <vector>

class Solution {
public:
  int minPathSum(std::vector<std::vector<int>> &grid) {
    int n = grid.size(), m = n ? grid[0].size() : 0;
    if (!m) {
      return 0;
    }
    for (int i = 1; i < m; ++i) {
      grid[0][i] += grid[0][i - 1];
    }
    for (int i = 1; i < n; ++i) {
      grid[i][0] += grid[i - 1][0];
      for (int j = 1; j < m; ++j) {
        grid[i][j] += std::min(grid[i][j - 1], grid[i - 1][j]);
      }
    }
    return grid[n - 1][m - 1];
  }
};
