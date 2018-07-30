#include <vector>
#include <cstdint>

class Solution {
public:
  int findPaths(int m, int n, int N, int i, int j) {
    if (!N) {
      return 0;
    }
    std::vector<std::vector<int>> dp(m + 2, std::vector<int>(n + 2)), dp_(dp);
    for (int i = 1; i <= m; ++i) {
      ++dp_[i][1];
      ++dp_[i][n];
    }
    for (int i = 1; i <= n; ++i) {
      ++dp_[1][i];
      ++dp_[m][i];
    }
    auto sum = dp_;
    const int mod = 1000000007;
    for (int i = 2; i <= N; ++i) {
      for (int x = 1; x <= m; ++x) {
        for (int y = 1; y <= n; ++y) {
          sum[x][y] += dp[x][y] = (int64_t(dp_[x][y + 1]) + dp_[x][y - 1] +
                      dp_[x - 1][y] + dp_[x + 1][y]) %
                     mod;
          sum[x][y] %= mod;
        }
      }
      std::swap(dp, dp_);
    }
    return sum[i + 1][j + 1];
  }
};
