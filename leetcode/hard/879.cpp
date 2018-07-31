#include <vector>

class Solution {
public:
  int profitableSchemes(int G, int P, std::vector<int> &group,
                        std::vector<int> &profit) {
    std::vector<std::vector<int>> dp(G + 1, std::vector<int>(P + 1));
    const int mod = 1000000007;
    dp[0][0] = 1;
    for (int k = 0, ks = group.size(); k < ks; ++k) {
      int g = group[k];
      int p = profit[k];
      for (int i = G - g; i >= 0; --i) {
        for (int j = P; j >= 0; --j) {
          int j1 = j + p;
          if (j1 > P) {
            j1 = P;
          }
          dp[i + g][j1] = (dp[i + g][j1] + dp[i][j]) % mod;
        }
      }
    }
    int ans = 0;
    for (int i = 1; i <= G; ++i) {
      ans = (ans + dp[i][P]) % mod;
    }
    return ans;
  }
};
