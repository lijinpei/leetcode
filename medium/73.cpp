#include <iostream>
#include <vector>

class Solution {
public:
  void setZeroes(std::vector<std::vector<int>>& matrix) {
    int m = matrix.size(), n = m ? matrix[0].size() : 0;
    auto dump = [&]() {
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
      }
    };
    if (!n) {
      return;
    }
    dump();
    bool fill_row = false;
    for (int x = 0; x < n; ++x) {
      if (!matrix[0][x]) {
        fill_row = true;
      }
    }
    bool fill_col = false;
    for (int x = 0; x < m; ++x) {
      if (!matrix[x][0]) {
        fill_col = true;
      }
    }
    if (m == 1) {
      if (fill_row) {
        for (int x = 0; x < n; ++x) {
          matrix[0][x] = 0;
        }
        return;
      }
    }
    if (n == 1) {
      if (fill_col) {
        for (int x = 0; x < m; ++x) {
          matrix[x][0] = 0;
        }
        return;
      }
    }
    int x = 0;
    for (;x + 2 < m && x + 2 < n; ++x) {
      if (fill_row || fill_col) {
        matrix[x][x] = 0;
      }
      bool fill_row1 = false;
      for (int p = x + 1; p < n; ++p) {
        if (matrix[x][p]) {
          if (matrix[x + 1][p]) {
            continue;
          } else {
            fill_row1 = true;
            for (int y = 0; y <= x; ++y) {
              matrix[y][p] = 0;
            }
          }
        } else {
          if (matrix[x + 1][p]) {
            matrix[x + 1][p] = 0;
          } else {
            fill_row1 = true;
            continue;
          }
        }
      }
      bool fill_col1 = false;
      for (int p = x + 1; p < m; ++p) {
        if (matrix[p][x]) {
          if (matrix[p][x + 1]) {
            continue;
          } else {
            fill_col1 = true;
            for (int y = 0; y <= x; ++y) {
              matrix[p][y] = 0;
            }
          }
        } else {
          if (matrix[p][x + 1]) {
            matrix[p][x + 1] = 0;
          } else {
            fill_col1 = true;
            continue;
          }
        }
      }
      if (fill_row) {
        for (int i = x; i < n; ++i) {
          matrix[x][i] = 0;
        }
      }
      if (fill_row1) {
        for (int i = 0; i <= x; ++i) {
          matrix[x + 1][i] = 0;
        }
      }
      fill_row = fill_row1;
      if (fill_col) {
        for (int i = x; i < m; ++i) {
          matrix[i][x] = 0;
        }
      }
      if (fill_col1) {
        for (int i = 0; i < x; ++i) {
          matrix[i][x + 1] = 0;
        }
      }
      fill_col = fill_col1;
      //dump();
    }
    if (fill_row || fill_col) {
      matrix[x][x] = 0;
    }
    if (x + 2 == m) {
      bool fill_row1 = false;
      for (int p = x + 1; p < n; ++p) {
        if (matrix[m - 2][p]) {
          if (matrix[m - 1][p]) {
            continue;
          } else {
            fill_row1 = true;
            for (int x = 0; x + 1 < m; ++x) {
              matrix[x][p] = 0;
            }
          }
        } else {
          if (matrix[m - 1][p]) {
            matrix[m - 1][p] = 0;
          } else {
            fill_row1 = true;
            continue;
          }
        }
      }
      if (!matrix[m - 1][x]) {
        for (int p = x + 1; p < n; ++p) {
          matrix[m - 1][p] = 0;
        }
      }
      if (fill_row1) {
        for (int p = 0; p < n; ++p) {
          matrix[m - 1][p] = 0;
        }
      }
      if (fill_row) {
        for (int p = x; p < n; ++p) {
          matrix[m - 2][p] = 0;
        }
      }
      if (fill_col) {
        matrix[x + 1][x] = 0;
      }
    } else {
      bool fill_col1 = false;
      for (int p = x + 1; p < m; ++p) {
        if (matrix[p][x]) {
          if (matrix[p][n - 1]) {
            continue;
          } else {
            fill_col1 = true;
            for (int x = 0; x + 1 < n; ++x) {
              matrix[p][x] = 0;
            }
          }
        } else {
          if (matrix[p][n - 1]) {
            matrix[p][n - 1] = 0;
          } else {
            fill_col1 = true;
            continue;
          }
        }
      }
      if (!matrix[x][n - 1]) {
        for (int p = x + 1; p < m; ++p) {
          matrix[p][n - 1] = 0;
        }
      }
      if (fill_col1) {
        for (int p = 0; p < m; ++p) {
          matrix[p][n - 1] = 0;
        }
      }
      if (fill_row) {
        matrix[x][n - 1] = 0;
      }
      if (fill_col) {
        for (int p = x + 1; p < m; ++p) {
          matrix[x][p] = 0;
        }
      }
    }
    dump();
  }
};

int main() {
  std::vector<std::vector<int>> input(5, std::vector<int>(7, 1));
  input[0][6] = 0;
  input[2][6] = 0;
  input[3][5] = 0;
  input[4][6] = 0;
  Solution sol;
  sol.setZeroes(input);
}
