#include <vector>

class NumMatrix {
  int n, m;
  std::vector<std::vector<int>> sum;
public:
    NumMatrix(std::vector<std::vector<int>> matrix) {
      int n = matrix.size();
      int m = n ? matrix[0].size() : 0;
      if (!m) {
        return;
      }
      sum = std::move(matrix);
      /*
      sum.resize(n);
      for (int i = 0; i < n; ++i) {
        sum[i] = std::move(matrix[i]);
      }
      */
      for (int i = 1; i < m; ++i) {
        sum[0][i] += sum[0][i - 1];
      }
      for (int i = 1; i < n; ++i) {
        int s = 0;
        for (int j = 0; j < m; ++j) {
          s += sum[i][j];
          sum[i][j] = s + sum[i - 1][j];
        }
      }
    }
   
    int sumRegion(int row1, int col1, int row2, int col2) {
      row1 -= 1;
      col1 -= 1;
      int b1 = row1 >= 0;
      int b2 = col1 >= 0;
      auto sum_ = [&](int r, int c, bool b) {
        return b ? sum[r][c] : 0;
      };
      return sum[row2][col2] + sum_(row1, col1, b1 && b2) - sum_(row2, col1, b2) -
             sum_(row1, col2, b1);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */
