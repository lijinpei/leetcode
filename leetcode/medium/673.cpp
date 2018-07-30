#include <vector>

class Solution {
public:
  int findNumberOfLIS(std::vector<int> &nums) {
    int n = nums.size();
    if (!n) {
      return 0;
    }
    std::vector<std::pair<int, int>> dp(n);
    dp[0] = {1, 1};
    int ans_l = 1, ans_v = 1;
    for (int i = 1; i < n; ++i) {
      int ml = 0, mv = 1;
      int v = nums[i];
      for (int j = 0; j < i; ++j) {
        if (nums[j] >= v) {
          continue;
        }
        auto p = dp[j];
        if (p.second > ml) {
          ml = p.second;
          mv = p.first;
        } else if (p.second == ml) {
          mv += p.first;
        }
      }
      ++ml;
      dp[i] = {mv, ml};
      if (ml > ans_l) {
        ans_l = ml;
        ans_v = mv;
      } else if (ml == ans_l) {
        ans_v += mv;
      }
    }
    return ans_v;
  }
};
