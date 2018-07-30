#include <algorithm>
#include <vector>

class Solution {
public:
  std::vector<int> largestDivisibleSubset(std::vector<int> &nums) {
    if (nums.empty()) {
      return {};
    }
    std::sort(nums.begin(), nums.end());
    nums.resize(
        std::distance(nums.begin(), std::unique(nums.begin(), nums.end())));
    int n = nums.size();
    std::vector<int> dp(n), fa(n);
    dp[0] = 1;
    int ans_v = 1, ans_p = 0;
    for (int i = 1; i < n; ++i) {
      int mv = 0, mp = -1;
      int v = nums[i];
      for (int j = 0; j < i; ++j) {
        if (!(v % nums[j])) {
          if (dp[j] > mv) {
            mv = dp[j];
            mp = j;
          }
        }
      }
      dp[i] = mv + 1;
      fa[i] = mp;
      if (mv >= ans_v) {
        ans_v = mv + 1;
        ans_p = i;
      }
    }
    dp.resize(ans_v);
    for (int i = ans_v - 1; i >= 0; --i) {
      dp[i] = nums[ans_p];
      ans_p = fa[ans_p];
    }
    return dp;
  }
};
