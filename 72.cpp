#include <string>
#include <vector>
#include <numeric>

class Solution {
public:
  int minDistance(const std::string & word1, const std::string & word2) {
    int s1 = word1.size(), s2 = word2.size();
    if (!s1 || !s2) {
      return s1 + s2;
    }
    std::vector<int> dp(s2), dp1(s2);
    std::iota(dp1.begin(), dp1.end(), 1);
    for (int i = 0; i < s1; ++i) {
      if (word1[i] == word2[0]) {
        dp[0] = i;
      } else {
          dp[0] = std::min(dp1[0], i) + 1;
      }
      for (int j = 1; j < s2; ++j) {
        if (word1[i] == word2[j]) {
          dp[j] = dp1[j - 1];
        } else {
          dp[j] = std::min(std::min(dp1[j], dp1[j - 1]), dp[j - 1]) + 1;
        }
      }
      std::swap(dp, dp1);
    }
    return dp1[s2 - 1];
  }
};
