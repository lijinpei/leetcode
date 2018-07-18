#include <vector>
#include <string>

class Solution {
public:
  std::vector<std::string> generateParenthesis(int n) {
    std::vector<std::vector<std::string>> dp(n + 1);
    dp[0].push_back("");
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < i; ++j) {
        int k = i - j - 1;
        for (std::size_t jn = 0; jn < dp[j].size(); ++jn) {
          for (std::size_t kn = 0; kn < dp[k].size(); ++kn) {
            std::string str;
            str.reserve(2 * i);
            str = dp[k][kn];
            str.push_back('(');
            str += dp[j][jn];
            str.push_back(')');
            dp[i].push_back(str);
          }
        }
      }
    }
    return std::move(dp[n]);
  }
};
