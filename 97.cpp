#include <string>
#include <vector>

class Solution {
public:
  bool isInterleave(std::string & str1, std::string & str2, const std::string & str3) {
    int s1 = str1.size(), s2 = str2.size(), s3 = str3.size();
    if (s1 + s2 != s3) {
      return false;
    }
    if (s1 > s2) {
      std::swap(s1, s2);
      std::swap(str1, str2);
    }
    std::vector<bool> dp(s1 + 1, true);
    for (int i = 1; i <= s1; ++i) {
      if (str1[i - 1] != str3[i - 1]) {
        for (; i <= s1; ++i) {
          dp[i] = false;
        }
        break;
      }
    }
    for (int j = 1; j <= s2; ++j) {
      dp[0] = (str2[j - 1] == str3[j - 1]) && dp[0];
      for (int i = 1; i <= s1; ++i) {
        char c3 = str3[i + j - 1];
        dp[i] = (str2[j - 1] == c3 && dp[i]) || (str1[i - 1] == c3 && dp[i - 1]);
      }
    }
    return dp[s1];
  }
};
