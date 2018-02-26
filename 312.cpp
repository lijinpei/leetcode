#include <vector>
#include <iostream>

class Solution {
public:
  int maxCoins(std::vector<int> &nums) {
    int s = nums.size();
    nums.insert(nums.end(), 1);
    nums.insert(nums.begin(), 1);
    std::vector<std::vector<int>> dp(s + 2, std::vector<int>(s + 2, 0));
    for (int l = 1; l <= s; ++l) {
      for (int i = 1, i1 = s - l + 1; i <= i1; ++i) {
        int v = 0;
        for (int j = i, j1 = i + l - 1; j <= j1; ++j) {
          int nv = nums[j] * nums[i - 1] * nums[j1 + 1];
          nv += dp[i][j - 1] + dp[j + 1][j1];
          v = std::max(v, nv);
        }
        dp[i][i + l - 1] = v;
      }
    }
    return dp[1][s];
  }
};

int main() {
  Solution sol;
  std::vector<int> input{3, 1, 5, 8};
  auto ret = sol.maxCoins(input);
  std::cout << ret << std::endl;
}

