#include <vector>

class Solution {
public:
  int coinChange(std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, -1);
    dp[0] = 0;
    for (int i = 0, s = coins.size(); i < s; ++i) {
      int v = coins[i];
      for (int j = v; j <= amount; ++j) {
        int v1 = dp[j - v];
        if (v1 < 0) {
          continue;
        }
        int & v2 = dp[j];
        if (v2 < 0 || v2 > v1 + 1) {
          v2 = v1 + 1;
        }
      }
    }
    return dp[amount];
  }
};
