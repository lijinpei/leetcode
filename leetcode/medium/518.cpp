#include <vector>
#include <cstdint>
#include <limits>

class Solution {
public:
  int change(int amount, std::vector<int> &coins) {
    std::vector<uint32_t> dp(amount + 1);
    dp[0] = 1;
    for (auto c : coins) {
      for (int i = 0; i + c <= amount; ++i) {
        dp[i + c] += dp[i];
      }
    }
    return dp[amount];
  }
};
