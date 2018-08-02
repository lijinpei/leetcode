class Solution {
public:
    int minSteps(int n) {
      if (n <= 1) {
        return 0;
      }
      int ret = 0;
      int i = 2;
      while (n != 1) {
        while (!(n % i)) {
          ret += i;
          n /= i;
        }
        ++i;
      }
      return ret;
    }
};
