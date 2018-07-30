#include <vector>

class Solution {
public:
  int orderOfLargestPlusSign(int N, std::vector<std::vector<int>>& mines) {
    std::vector<std::vector<bool>> map(N, std::vector<bool>(N));
    for (const auto & pq : mines) {
      map[pq[0]][pq[1]] = true;
    }
    std::vector<int> dp1(N), dp2(N);
    std::vector<std::vector<int>> dp3(N, std::vector<int>(N));
    for (int i = N - 2; i >= 0; --i) {
      for (int j = 0; j < N; ++j) {
        if (map[i + 1][j]) {
          dp3[i][j] = 0;
        } else {
          dp3[i][j] = dp3[i + 1][j] + 1;
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) {
      for (int j = N - 2; j >= 0; --j) {
        if (map[i][j + 1]) {
          dp2[j] = 0;
        } else {
          dp2[j] = dp2[j + 1] + 1;
        }
      }
      int dp4 = 0;
      for (int j = 0; j < N; ++j) {
        if (map[i][j]) {
          dp4 = 0;
          dp1[j] = 0;
        } else {
          int nv = std::min(std::min(dp1[j], dp2[j]), std::min(dp3[i][j], dp4)) + 1;
          if (nv > ans) {
            ans = nv;
          }
          ++dp4;
          ++dp1[j];
        }
      }
    }
    return ans;
  }
};
