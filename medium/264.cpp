#include <vector>

class Solution {
public:
  int nthUglyNumber(int n) {
    std::vector<int> ugly(n);
    ugly[0] = 1;
    int p2 = 1, p3 = 1, p5 = 1;
    int v2 = 2, v3 = 3, v5 = 5;
    for (int i = 1; i < n; ++i) {
      if (v2 == v3) {
        if (p2 < i) {
          v2 = ugly[p2++] * 2;
        } else {
          v3 = ugly[p3++] * 3;
        }
      }
      if (v2 < v3) {
        if (v2 == v5) {
          if (p2 < i) {
            v2 = ugly[p2++] * 2;
          } else {
            v5 = ugly[p5++] * 5;
          }
        }
        if (v2 < v5) {
          ugly[i] = v2;
          v2 = ugly[p2++] * 2;
        } else {
          ugly[i] = v5;
          v5 = ugly[p5++] * 5;
        }
      } else {
        if (v3 == v5) {
          if (p3 < i) {
            v3 = ugly[p3++] * 3;
          } else {
            v5 = ugly[p5++] * 5;
          }
        }
        if (v3 < v5) {
          ugly[i] = v3;
          v3 = ugly[p3++] * 3;
        } else {
          ugly[i] = v5;
          v5 = ugly[p5++] * 5;
        }
      }
    }
    return ugly[n - 1];
  }
};
