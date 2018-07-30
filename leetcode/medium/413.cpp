#include <vector>

class Solution {
public:
  int numberOfArithmeticSlices(vector<int> &A) {
    int n = A.size();
    if (n < 3) {
      return 0;
    }
    int d = A[1] - A[0], l = 2, ans = 0, lv = A[1];
    for (int i = 2; i < n; ++i) {
      int nv = A[i];
      if (nv == lv + d) {
        ++l;
      } else {
        ans += l * (l - 2) / 2 - (l - 1);
        l = 2;
        d = nv - lv;
      }
      lv = nv;
    }
    return ans + l * (l - 2) / 2 - (l - 1);
  }
};
