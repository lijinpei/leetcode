#include <vector>
#include <algorithm>

class Solution {
public:
  bool PredictTheWinner(std::vector<int> &nums) {
    int n = nums.size();
    if (n <= 1) {
      return true;
    }
    std::vector<std::vector<int>> dp(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
      dp[i][i] = nums[i];
    }
    for (int l = 2; l <= n; ++l) {
      for (int i = 0; i + l <= n; ++i) {
        int v1 = nums[i] - dp[i + 1][i + l - 1];
        int v2 = nums[i + l - 1] - dp[i][i + l - 2];
        dp[i][i + l - 1] = std::max(v1, v2);
      }
    }
    return dp[0][n - 1] >= 0;
  }
};
