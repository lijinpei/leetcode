#include <algorithm>
#include <vector>

class Solution {
public:
  bool searchMatrix(std::vector<std::vector<int>> &matrix, int target) {
    int n = matrix.size();
    int p = n ? matrix[0].size() : 0;
    if (!p) {
      return false;
    }
    for (int i = 0; i < n; ++i) {
      auto & m = matrix[i];
      p = std::distance(m.begin(), std::upper_bound(m.begin(), m.begin() + p, target));
      if (!p) {
        return false;
      }
      if (m[p - 1] == target) {
        return true;
      }
    }
    return false;
  }
};
