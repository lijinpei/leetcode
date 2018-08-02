class Solution {
public:
    int uniquePaths(int m, int n) {
      m -= 1;
      n -= 1;
      if (m > n) {
        std::swap(m, n);
      }
      int s = m + n;
      int ans = 1;
      for (int i = 1; i <= m; ++i) {
        ans = int64_t(ans) * s / i;
        --s;
      }
      return ans;
    }
};
