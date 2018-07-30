#include <string>
#include <vector>
#include <climits>

class Solution {
public:
  int minCut(const std::string & str) {
    int s = str.size();
    std::vector<int> dp(s + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 0; i < s; ++i) {
      auto update = [](int & v1, int v2) {
        if (v2 < v1) {
          v1 = v2;
        }
      };
      int l1 = i, l2 = s - i;
      update(dp[i + 1], dp[i] + 1);
      for (int le = std::min(l1, l2), l = 1; l <= le; ++l) {
        if (str[i - l] != str[i + l]) {
          break;
        }
        update(dp[i + l + 1], dp[i - l] + 1);
      }
      for (int le = std::min(l1 + 1, l2), l = 1; l <= le; ++l) {
        if (str[i - l + 1] != str[i + l]) {
          break;
        }
        update(dp[i + l + 1], dp[i - l + 1] + 1);
      }
    }
    return dp[s] - 1;
  }
};

