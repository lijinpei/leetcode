#include <vector>
#include <cstring>

class Solution {
  static constexpr int NMAX = 100;
  int val[NMAX + 1][NMAX + 1][NMAX + 1];
  std::vector<std::pair<int, int>> arr;
  int unique(std::vector<int> & boxes) {
    int l = boxes.size();
    arr.resize(0);
    arr.reserve(l);
    int c = boxes[0], cn = 1;
    for (int i = 1; i < l; ++i) {
      if (boxes[i] == c) {
        ++cn;
      } else {
        arr.emplace_back(c, cn);
        c = boxes[i];
        cn = 1;
      }
    }
    arr.emplace_back(c, cn);
    return arr.size();
  }
  int dp(int l, int r, int k) {
    if (l == r) {
      int v = arr[r].second;
      return val[l][r][k] = (k + v) * (k + v);
    }
    if (val[l][r][k]) {
      return val[l][r][k];
    }
    int c = arr[r].first, v = arr[r].second;
    int ans = (v + k) * (v + k) + dp(l, r - 1, 0);
    for (int i = l; i + 1 < r; ++i) {
      if (arr[i].first != c) {
        continue;
      }
      int ans1 = dp(i + 1, r - 1, 0) + dp(l, i, k + v);
      if (ans1 > ans) {
        ans = ans1;
      }
    }
    return val[l][r][k] = ans;
  }
public:
  int removeBoxes(std::vector<int> &boxes) {
    memset(&val[0][0][0], 0, sizeof(val));
    int l = unique(boxes);
    return dp(0, l - 1, 0);
  }
};
