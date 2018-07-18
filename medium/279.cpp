#include <vector>
#include <numeric>

class Solution {
public:
  int numSquares(int n) {
    std::vector<int> dp(n + 1);
    std::iota(dp.begin(), dp.end(), 0);
    for (int i = 2, v = i * i; v > 0 && v <= n;) {
      for (int j = 0; j + v <= n; ++j) {
        int v1 = dp[j] + 1;
        int & v2 = dp[j + v];
        if (v1 < v2) {
          v2 = v1;
        }
      }
      ++i;
      v = i * i;
    }
    return dp[n];
  }
};
