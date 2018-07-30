#include <string>
#include <vector>
#include <iostream>

class Solution {
public:
  int numDistinct(const std::string & S, const std::string & T) {
    int ss = S.size(), ts = T.size();
    std::vector<int> dp(ts + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < ss; ++i) {
      for (int j = ts; j; --j) {
        if (S[i] == T[j - 1]) {
          dp[j] += dp[j - 1];
        }
      }
    }
    return dp[ts];
  }
};

int main() {
  Solution sol;
  auto ret = sol.numDistinct("rabbbit", "rabbit");
  std::cout << ret << std::endl;
}
