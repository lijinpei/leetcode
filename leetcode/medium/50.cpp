class Solution {
public:
  double myPow(double x, int n) {
    if (x == 0) {
      return 0;
    }
    if (!n) {
      return 1;
    }
    if (n < 0) {
      x = 1 / x;
      n = -n;
    }
    double xn = x;
    int k = 1;
    double ret = 1;
    while (n) {
      if (n & k) {
        ret *= xn;
        n = n & ~k;
      }
      k <<= 1;
      xn *= xn;
    }
    return ret;
  }
};

