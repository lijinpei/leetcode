#include <vector>

class Solution {
public:
  int minSteps(int n) {
    std::vector<int> dp(n + 1);
    dp[1] = 0;
    for (int i = 2; i <= n; ++i) {
      int v = i;
      for (int j = 2; j * j <= i; ++j) {
        int v1 = i / j;
        int v2 = i % j;
        if (v2) {
          continue;
        }
        int v3 = dp[v1] + j;
        if (v3 < v) {
          v = v3;
        }
        v3 = dp[j] + v1;
        if (v3 < v) {
          v = v3;
        }
      }
      dp[i] = v;
    }
    return dp[n];
  }
};
