#include <vector>

class Solution {
public:
  bool canPartition(std::vector<int>& nums) {
    int sum = 0;
    for (auto v : nums) {
      sum += v;
    }
    if (sum & 1) {
      return false;
    }
    int target = sum / 2;
    std::vector<bool> dp(target + 1);
    dp[0] = true;
    int s = 0;
    for (auto v : nums) {
      for (int v2 = std::min(target - v, s); v2 >= 0; v2--) {
        if (dp[v2]) {
          dp[v2 + v] = true;
        }
      }
      if (dp[target]) {
        return true;
      }
      s = std::min(s + v, target);
    }
    return false;
  }
};
