#include <vector>

class Solution {
public:
  std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    if (!n) {
      return {};
    }
    int m = matrix[0].size();
    if (!m) {
      return {};
    }
    std::vector<int> ret(n * m);
    int i = 0;
    int x1 = 0, x2 = n, y1 = 0, y2 = m;
    while (true) {
      for (int y = y1; y < y2; ++y) {
        ret[i++] = matrix[x1][y];
      }
      ++x1;
      if (x1 == x2) {
        break;
      }
      for (int x = x1; x < x2; ++x) {
        ret[i++] = matrix[x][y2 - 1];
      }
      --y2;
      if (y1 == y2) {
        break;
      }
      for (int y = y2 - 1; y >= y1; --y) {
        ret[i++] = matrix[x2 - 1][y];
      }
      --x2;
      if (x1 == x2) {
        break;
      }
      for (int x = x2 - 1; x >= x1; --x) {
        ret[i++] = matrix[x][y1];
      }
      ++y1;
      if (y1 == y2) {
        break;
      }
    }
    return ret;
  }
};

