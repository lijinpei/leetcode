class Solution {
public:
  int findIntegers(int n) {
    int a = 1, b = 1, ans = 0, f = 1;
    while (n) {
      if ((n & 3) == 3) {
        ans = 0;
        f = 0;
      }
      if (n & 1) {
        ans += b;
      }
      int tmp = b;
      b += a;
      a = tmp;
      n >>= 1;
    }
    return ans + f;
  }
};
