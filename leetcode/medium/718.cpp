#include <vector>

class Solution {
public:
  int findLength(std::vector<int> &A, std::vector<int> &B) {
    int la = A.size(), lb = B.size();
    if (la > lb) {
      std::swap(A, B);
      std::swap(la, lb);
    }
    std::vector<int> dp1(la + 1), dp2(lb + 1);
    int ans = 0;
    for (int i = 0; i < lb; ++i) {
      int b = B[i];
      for (int j = 0; j < la; ++j) {
        if (b == A[j]) {
          int nv = dp1[j] + 1;
          dp2[j + 1] = nv;
          if (nv > ans) {
            ans = nv;
          }
        } else {
          dp2[j + 1] = 0;
        }
      }
      std::swap(dp1, dp2);
    }
    return ans;
  }
};
