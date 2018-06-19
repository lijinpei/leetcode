#include <utility>
#include <vector>

class Solution {
public:
  void rotate(std::vector<std::vector<int>> &matrix) {
    auto n = matrix.size();
    for (size_t i = 0, i1 = (n + 1) >> 1; i < i1; ++i) {
      for (size_t j = 0, j1 = n >> 1; j < j1; ++j) {
        matrix[j][n - 1 - i] = std::exchange(
            matrix[i][j],
            std::exchange(matrix[n - 1 - j][i],
                          std::exchange(matrix[n - 1 - i][n - 1 - j],
                                        matrix[j][n - 1 - i])));
      }
    }
  }
};
