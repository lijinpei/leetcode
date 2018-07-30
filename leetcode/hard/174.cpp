#include <vector>
#include <climits>

class Solution {
public:
  int calculateMinimumHP(std::vector<std::vector<int>>& dungeon) {
    auto calc = [](int & v1, int v2, int v3) {
      v1 = std::min(v1, v2) - v3;
      if (v1 <= 0) {
        v1 = 1;
      }
    };
    int m = dungeon.size();
    int n = dungeon[0].size();
    std::vector<int> dp(m + 1, INT_MAX);
    dp[m - 1] = 1;
    for (int j = n - 1; j >= 0; --j) {
      for (int i = m - 1; i >= 0; --i) {
        calc(dp[i], dp[i + 1], dungeon[i][j]);
      }
    }
    return dp[0];
  }
};
