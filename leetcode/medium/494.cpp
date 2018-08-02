#include <unordered_map>
#include <vector>

class Solution {
  class SolutionImpl {
    std::vector<int> & nums;
    std::vector<std::unordered_map<int, int>> dp;
    int calc(int s, int n) {
      if (n == -1) {
        return s == 0 ? 1 : 0;
      }
      auto itor = dp[n].find(s);
      if (itor != dp[n].end()) {
        return itor->second;
      }
      int v = calc(s + nums[n], n - 1) + calc(s - nums[n], n - 1);
      return dp[n][s] = v;
    }
  public:
    SolutionImpl(std::vector<int> & nums) : nums(nums), dp(nums.size()) {}
    int calc(int S) {
      return calc(S, nums.size() - 1);
    }
  };
public:
  int findTargetSumWays(std::vector<int> &nums, int S) {
    return SolutionImpl(nums).calc(S);
  }
};
