#include <vector>
#include <limits>

class Solution {
public:
  int minSwap(std::vector<int> &A, std::vector<int> &B) {
    int n = A.size();
    if (n == 1) {
      return 0;
    }
    const int large = std::numeric_limits<int>::max() / 2;
    int s0 = 0, s1 = 1;
    int a = A[0], b = B[0];
    for (int i = 1; i < n; ++i) {
      int na = A[i], nb = B[i];
      int n0, n1;
      if (na > a && nb > b) {
        n0 = s0, n1 = s1 + 1;
      } else {
        n0 = large, n1 = large;
      }
      if (na > b && nb > a) {
        if (s1 < n0) {
          n0 = s1;
        }
        if (s0 + 1 < n1) {
          n1 = s0 + 1;
        }
      }
      s0 = n0;
      s1 = n1;
      a = na;
      b = nb;
    }
    return s1 < s0 ? s1 : s0;
  }
};
