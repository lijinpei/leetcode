#include <vector>
#include <cstdint>

class Solution {
public:
  int maxRotateFunction(std::vector<int> &A) {
    int n = A.size();
    if (!n) {
      return 0;
    }
    int64_t s1 = 0, s2 = 0;
    for (int i = 0; i < n; ++i) {
      int v = A[i];
      s1 += v;
      s2 += i * v;
    }
    int64_t ans = s2;
    for (int i = n - 1; i; --i) {
      int v = A[i];
      s2 += s1 - n * v;
      if (s2 > ans) {
        ans = s2;
      }
    }
    return ans;
  }
};
