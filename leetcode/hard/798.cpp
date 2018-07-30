#include <vector>

class Solution {
public:
  int bestRotation(std::vector<int> &A) {
    int n = A.size();
    if (!n) {
      return 0;
    }
    std::vector<int> K(n);
    int k0 = 0;
    for (int i = 0; i < n; ++i) {
      int v = A[i];
      if (v >= n) {
        continue;
      }
      if (i == v) {
        ++k0;
        K[1] += -1;
        K[v + 1] += 1;
      } else if (v > i) {
        K[i + 1] += 1;
        K[i - v + 1 + n] += -1;
      } else {
        k0 += 1;
        K[i - v + 1] += -1;
        K[i + 1] += 1;
      }
    }
    int mp = 0, mv = k0;
    for (int k = 1; k < n; ++k) {
      k0 = k0 + K[k];
      if (k0 > mv) {
        mv = k0;
        mp = k;
      }
    }
    return mp;
  }
};
