#include <vector>

class Solution {
  static constexpr int NMAX = 10000;
  std::vector<int> dp;
  static int ilog2(int x) {

    int i, j, k, l, m;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);

    // i = 0x55555555
    i = 0x55 | (0x55 << 8);
    i = i | (i << 16);

    // j = 0x33333333
    j = 0x33 | (0x33 << 8);
    j = j | (j << 16);

    // k = 0x0f0f0f0f
    k = 0x0f | (0x0f << 8);
    k = k | (k << 16);

    // l = 0x00ff00ff
    l = 0xff | (0xff << 16);

    // m = 0x0000ffff
    m = 0xff | (0xff << 8);

    x = (x & i) + ((x >> 1) & i);
    x = (x & j) + ((x >> 2) & j);
    x = (x & k) + ((x >> 4) & k);
    x = (x & l) + ((x >> 8) & l);
    x = (x & m) + ((x >> 16) & m);
    x = x + ~0;
    return x + 1;
  }

  int calc(int t) {
    if (dp[t]) {
      return dp[t];
    }
    int n = ilog2(t);
      //std::cout << t << ' ' << n << std::endl;
    if ((1 << n) == t + 1) {
      return dp[t] = n;
    }
    int v = n + 1 + calc((1 << n) - 1 - t);
    for (int m = 0; m + 1 < n; ++m) {
      int nv = n + m + 1 + calc(t - (1 << (n - 1)) + (1 << m));
      if (nv < v) {
        v = nv;
      }
    }
    return dp[t] = v;
  }
public:
  int racecar(int target) {
    dp.resize(0);
    dp.resize(NMAX + 1);
    return calc(target);
  }
};
