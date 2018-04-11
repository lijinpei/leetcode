#include <vector>
#include <set>
#include <limits>

class Solution {
public:
  int maxSumSubmatrix(std::vector<std::vector<int>> &matrix, int K) {
    int n = matrix.size();
    int m = n ? matrix[0].size() : 0;
    int ret = std::numeric_limits<int>::min();
    if (!m) {
      return ret;
    }
    {
    std::set<int> S;
    S.insert(0);
    if (matrix[0][0] <= K) {
      ret = matrix[0][0];
    }
    S.insert(matrix[0][0]);
    for (int i = 1; i < m; ++i) {
      int s = matrix[0][i] += matrix[0][i - 1];
      auto itor = S.lower_bound(s - K);
      if (itor != S.end()) {
        int nv = s - *itor;
        if (nv > ret) {
          ret = nv;
        }
      }
      S.insert(s);
    }
    }
    for (int i = 1; i < n; ++i) {
      int s = matrix[i][0];
      int s1 = matrix[i][0] += matrix[i - 1][0];
      std::set<int> S;
      S.insert(0);
      if (s1 <= K && s1 > ret) {
        ret = s1;
      }
      S.insert(s1);
      for (int j = 1; j < m; ++j) {
        s += matrix[i][j];
        int s1 = matrix[i][j] = s + matrix[i - 1][j];
        auto itor = S.lower_bound(s1 - K);
        if (itor != S.end()) {
          int nv = s1 - *itor;
          if (nv > ret) {
            ret = nv;
          }
        }
        S.insert(s1);
      }
    }
    for (int i = 0; i + 1 < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        std::set<int> S;
        S.insert(0);
        int s = matrix[j][0] - matrix[i][0];
        if (s <= K && s > ret) {
          ret = s;
        }
        S.insert(s);
        for (int k = 1; k < m; ++k) {
          s = matrix[j][k] - matrix[i][k];
          auto itor = S.lower_bound(s - K);
          if (itor != S.end()) {
            int nv = s - *itor;
            if (nv > ret) {
              ret = nv;
            }
          }
          S.insert(s);
        }
      }
    }
    return ret;
  }
};
