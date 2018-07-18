#include <vector>
#include <string>

class Solution {
public:
  int findMaxForm(const std::vector<std::string>& strs, int m, int n) {
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    std::vector<int> nmax(m + 1);
    int mmax = 0;
    for (const auto str : strs) {
      int mn = 0, nn = 0;
      for (char c : str) {
        if (c == '0') {
          ++mn;
        } else {
          ++nn;
        }
      }
      if (mn > m || nn > n) {
        continue;
      }
      for (int m1 = std::min(m - mn, mmax); m1 >= 0; --m1) {
        for (int n1 = std::min(n - nn, nmax[m1]); n1 >= 0; --n1) {
          int v = dp[m1][n1];
          if (!v) {
            continue;
          }
          int &v2 = dp[m1 + mn][n1 + nn];
          if (v >= v2) {
            v2 = v + 1;
            int n2 = n1 + nn;
            int & n3 = nmax[m1 + mn];
            if (n2 > n3) {
              n3 = n2;
            }
          }
        }
      }
      if (!dp[mn][nn]) {
        dp[mn][nn] = 1;
        nmax[mn] = std::max(nmax[mn], nn);
      }
      mmax = std::min(mmax + mn, m);
    }
    int ans = 0;
    for (int x = 0; x <= mmax; ++x) {
      for (int y = 0, y1 = nmax[x]; y <= y1; ++y) {
        int v = dp[x][y];
        if (v > ans) {
          ans = v;
        }
      }
    }
    return ans;
  }
};
