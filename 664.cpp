#include <string>
#include <vector>

class Solution {
public:
  int strangePrinter(std::string & str) {
    int s = str.size();
    if (!s) {
      return 0;
    }
    std::vector<std::vector<int>> dp(s + 1, std::vector<int>(s));
    for (int i = 0; i < s; ++i) {
      dp[i][i] = 1;
    }
    for (int l = 2; l <= s; ++l) {
      for (int i = 0, i1 = s - l; i <= i1; ++i) {
        int j = i + l - 1;
        int v = l;
        for (int k = i; k < j; ++k) {
          int v1 = dp[i][k] + dp[k + 1][j];
          v = std::min(v, v1);
        }
        if (str[j] == str[i]) {
          v = std::min(v, dp[i][j - 1]);
        }
        dp[i][j] = v;
      }
    }
    return dp[0][s - 1];
  }
};
