#include <vector>

class Solution {
public:
  bool searchMatrix(std::vector<std::vector<int>> &matrix, int target) {
    int n = matrix.size();
    int m = n ? matrix[0].size() : 0;
    if (!m) {
      return false;
    }
    for (int i = 0, lb = m - 1; i < n; ++i) {
      while (lb >= 0 && matrix[i][lb] > target) {
        --lb;
      }
      if (lb < 0) {
        return false;
      }
      if (matrix[i][lb] == target) {
        return true;
      }
    }
    return false;
  }
};
