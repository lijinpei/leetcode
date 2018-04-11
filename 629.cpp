#include <vector>

const int V = 1000000007;
class Solution {
public:
  int kInversePairs(int n, int k) {
    std::vector<int> dp(k + 1);
    dp[0] = 1;
    for (int i = 2; i <= n; ++i) {
      int jm = std::min(k, i * (i - 1) / 2);
      int jm0 = jm - i + 1;
      if (jm0 < 0) {
        jm0 = 0;
      }
      int s0 = 0;
      for (int j = jm0; j <= jm; ++j) {
        s0 += dp[j];
        if (s0 >= V) {
          s0 -= V;
        }
      }
      for (int j = jm; j >= 1; --j) {
        int v = dp[j];
        dp[j] = s0;
        s0 -= v;
        if (s0 < 0) {
          s0 += V;
        }
        if (j - i >= 0) {
          s0 += dp[j - i];
          if (s0 >= V) {
            s0 -= V;
          }
        }
      }
    }
    return dp[k];
  }
};
