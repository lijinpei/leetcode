#include <vector>

class Solution {
public:
  int numTrees(int n) {
    std::vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
      int s = 0;
      for (int j = 1; j <= i; ++j) {
        s += dp[j - 1] * dp[i - j];
      }
      dp[i] = s;
    }
    return dp[n];
  }
};
