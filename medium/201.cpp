#include <limits>

class Solution {
public:
  int rangeBitwiseAnd(int m_, int n_) {
    unsigned m = m_, n = n_, v1 = 1;
    int ret = 0;
    for (int i = 0; i < 31; ++i) {
      if (m == n && (m & 1)) {
        ret += v1;
      }
      v1 <<= 1;
      m >>= 1;
      n >>= 1;
      if (!(m & n)) {
        break;
      }
    }
    return ret;
  }
};
