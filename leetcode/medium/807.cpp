#include <vector>
#include <limits>

class Solution {
public:
  int maxIncreaseKeepingSkyline(std::vector<std::vector<int>> &grid) {
    int n = grid.size();
    int m = n ? grid[0].size() : 0;
    if (!m) {
      return 0;
    }
    std::vector<int> row_max(n, std::numeric_limits<int>::min()), col_max(m, std::numeric_limits<int>::min());
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int v = grid[i][j];
        row_max[i] = std::max(row_max[i], v);
        col_max[j] = std::max(col_max[j], v);
      }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      int r = row_max[i];
      for (int j = 0; j < m; ++j) {
        int v = grid[i][j];
        ans += std::min(r, col_max[j]) - v;
      }
    }
    return ans;
  }
};
