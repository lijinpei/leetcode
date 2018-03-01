#include <vector>

class Solution {
public:
  bool canCross(std::vector<int> &stones) {
    int s = stones.size();
    std::vector<std::vector<bool>> dp(s, std::vector<bool>(s, false));
    auto update = [&](int p1, int p2, int p3) {
      dp[p2][p3] = dp[p1][p2] | dp[p2][p3];
    };
    if (stones[1] == 1) {
      dp[0][1] = true;
    } else {
      return false;
    }
    for (int i = 2; i < s; ++i) {
      for (int j = 1, k = 0; j < i; ++j) {
        int d = stones[i] - stones[j] + 1;
        int d1 = stones[j] - d;
        while (k < j && stones[k] < d1) {
          ++k;
        }
        d1 += 2;
        int k1 = k;
        while (k1 < j) {
          if (stones[k1] <= d1) {
            ++k1;
          } else {
            break;
          }
        }
        if (k1 == k + 1) {
          update(k, j, i);
        } else if (k1 == k + 2) {
          update(k, j, i);
          update(k + 1, j, i);
        } else if (k1 == k + 3) {
          update(k, j, i);
          update(k + 1, j, i);
          update(k + 2, j, i);
        }
      }
    }
    for (int i = 0; i + 1 < s; ++i) {
      if (dp[i][s - 1]) {
        return  true;
      }
    }
    return false;
  }
};
