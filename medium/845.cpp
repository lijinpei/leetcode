#include <vector>

class Solution {
public:
  int longestMountain(std::vector<int>& A) {
    int s = A.size(), p = 0, ans = 0;
    auto increase = [&](int p) {
      while (p + 1 < s && A[p + 1] > A[p]) {
        ++p;
      }
      return p;
    };
    auto decrease = [&](int p) {
      while (p + 1 < s && A[p + 1] < A[p]) {
        ++p;
      }
      return p;
    };
    while (p < s) {
      int p1 = increase(p);
      if (p1 == p) {
        ++p;
        continue;
      }
      int p2 = decrease(p1);
      if (p2 == p1) {
        p = p1 + 1;
        continue;
      }
      ans = std::max(ans, p2 - p + 1);
      p = p2;
    }
    return ans;
  }
};
