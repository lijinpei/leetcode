#include <vector>

class Solution {
public:
  int maximalSquare(std::vector<std::vector<char>> &matrix) {
    int n = matrix.size();
    int m = n ? matrix[0].size() : 0;
    if (!m) {
      return 0;
    }
    std::vector<int> dp(m);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      dp[0] = matrix[i][0] == '1' ? 1 : 0;
      ans = std::max(ans, dp[0]);
      for (int j = 1, lv = dp[0]; j < m; ++j) {
        if (matrix[i][j] == '0') {
          dp[j] = 0;
          lv = 0;
        } else {
          int v1 = dp[j];
          if (v1 == lv) {
            lv = matrix[i - v1][j - v1] == '1' ? v1 + 1 : v1;
          } else {
            lv = std::min(v1, lv) + 1;
          }
          dp[j] = lv;
          ans = std::max(ans, lv);
        }
      }
    }
    return ans * ans;
  }
};
