#include <vector>
#include <unordered_map>
#include <limits>

class Solution {
public:
  int numberOfArithmeticSlices(std::vector<int> &A) {
    int n = A.size();
    std::vector<std::unordered_map<int, int>> dp(n);
    int64_t ans = 0;
    for (int i = 1; i < n; ++i) {
      int v1 = A[i];
      for (int j = 0; j < i; ++j) {
        int64_t v2 = A[j];
        int64_t v3 = v2 + v2 - v1;
        int ret = 1;
        if (v3 >= std::numeric_limits<int>::min() && v3 <= std::numeric_limits<int>::max()) {
          auto itor = dp[j].find(v3);
          if (itor != dp[j].end()) {
            ret += itor->second;
          }
        }
        auto & v = dp[i][v2];
        v += ret;
      }
      for (auto v : dp[i]) {
        ans += v.second;
      }
    }
    return ans - n * (n - 1) / 2;
  }
};
