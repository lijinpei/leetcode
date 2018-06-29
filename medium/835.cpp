#include <iostream>
#include <vector>

class Solution {
public:
  int largestOverlap(std::vector<std::vector<int>> &A,
                     std::vector<std::vector<int>> &B) {
    int ra = A.size(), ca = ra ? A[0].size() : 0;
    int rb = B.size(), cb = rb ? B[0].size() : 0;
    if (!ca || !cb) {
      return 0;
    }
    int ans = 0;
    for (int dr = -(ra - 1), dr1 = (rb - 1); dr <= dr1; ++dr) {
      for (int dc = -(ca - 1), dc1 = (cb - 1); dc <= dc1; ++dc) {
        int r1 = std::max(0, -dr);
        int r2 = std::min(ra, rb - dr);
        int c1 = std::max(0, -dc);
        int c2 = std::min(ca, cb - dc);
        int nv = 0;
        for (int r = r1; r < r2; ++r) {
          for (int c = c1; c < c2; ++c) {
            if (A[r][c] && B[r + dr][c + dc]) {
              ++nv;
            }
          }
        }
        std::cout << dr << ' ' << dc << ' ' << nv << std::endl;
        ans = std::max(ans, nv);
      }
    }
    return ans;
  }
};
