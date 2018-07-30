#include <limits>
#include <cstdint>

class Solution {
  static int64_t numOfZero(int64_t n) {
    int64_t ret = 0;
    while (n >= 5) {
      n /= 5;
      ret += n;
    }
    return ret;
  }
  static int64_t lowerBound(int64_t K) {
    int64_t l = 5, h = std::numeric_limits<int64_t>::max();
    while (l + 1 != h) {
      int64_t m = (h - l) / 2 + l;
      int64_t k1 = numOfZero(m);
      if (k1 <= K) {
        l = m;
      } else {
        h = m;
      }
    }
    return l + 1;
  }
public:
    int preimageSizeFZF(int K) {
      return lowerBound(K) - (K ? lowerBound(K - 1) : 1);
    }
};
