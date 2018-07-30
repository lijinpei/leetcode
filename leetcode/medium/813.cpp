#include <vector>

class Solution {
public:
  double largestSumOfAverages(std::vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<int> sum(n + 1);
    int s = 0;
    for (int i = 0; i < n; ++i) {
      s += nums[i];
      sum[i + 1] = s;
    }
    std::vector<double> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
      dp[i] = double(sum[i]) / i;
    }
    for (int kk = 1; kk < k; ++kk) {
      for (int i = n; i > kk; --i) {
        for (int j = i - 1; j >= kk; --j) {
          double nv = dp[j] + double(sum[i] - sum[j]) / (i - j);
          if (nv > dp[i]) {
            dp[i] = nv;
          }
        }
      }
    }
    return dp[n];
  }
};
