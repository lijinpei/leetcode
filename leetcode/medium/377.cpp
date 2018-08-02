#include <vector>

class Solution {
public:
  int combinationSum4(std::vector<int> &nums, int target) {
    std::vector<int> dp(target + 1);
    dp[0] = 1;
    for (int i = 0; i <= target; ++i) {
      for (auto n : nums) {
        if (i >= n) {
          dp[i] += dp[i - n];
        }
      }
    }
    return dp[target];
  }
};
