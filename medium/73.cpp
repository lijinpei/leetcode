#include <iostream>
#include <vector>
#include <cassert>

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
    bool need_fill_row = false, need_fill_col = false;
    bool last_fill_row = false, last_fill_col = false;
    for (int i = 0; i < n; ++i) {
      if (!matrix[0][i]) {
        need_fill_row = true;
      }
    }
    if (m == 1) {
      if (need_fill_row) {
        for (int i = 0; i < n; ++i) {
          matrix[0][i] = 0;
        }
      }
      return;
    }
    for (int i = 0; i < m; ++i) {
      if (!matrix[i][0]) {
        need_fill_col = true;
      }
    }
    if (n == 1) {
      if (need_fill_col) {
        for (int i = 0; i < m; ++i) {
          matrix[i][0] = 0;
        }
      }
      return;
    }
    for (int x = 0;; ++x) {
      std::cout << (need_fill_row ? "true" : "false") << ' ';
      std::cout << (need_fill_col ? "true" : "false") << ' ';
      std::cout << std::endl;
      bool need_fill_row1, need_fill_col1, last_fill_row1, last_fill_col1;
      auto do_fill_row = [&]() {
        if (need_fill_row) {
          if (!last_fill_row) {
            for (int y = 0; y < x; ++y) {
              matrix[x][y] = 0;
            }
          }
          for (int y = x; y < n; ++y) {
            matrix[x][y] = 0;
          }
        }
      };
      auto do_fill_col = [&]() {
        if (need_fill_col) {
          if (!last_fill_col) {
            for (int y = 0; y < x; ++y) {
              matrix[y][x] = 0;
            }
          }
          for (int y = x; y < m; ++y) {
            matrix[y][x] = 0;
          }
        }
      };
      auto propogate_row = [&]() {
        for (int p = x + 2; p < n; ++p) {
          if (matrix[x][p]) {
            if (matrix[x + 1][p]) {
              continue;
            } else {
              need_fill_row1 = true;
              for (int y = 0; y <= x; ++y) {
                matrix[y][p] = 0;
              }
            }
          } else {
            if (matrix[x + 1][p]) {
              matrix[x + 1][p] = 0;
            } else {
              need_fill_row1 = true;
            }
          }
        }
      };
      auto propogate_col = [&]() {
        for (int p = x + 2; p < m; ++p) {
          if (matrix[p][x]) {
            if (matrix[p][x + 1]) {
              continue;
            } else {
              need_fill_col1 = true;
              for (int y = 0; y <= x; ++y) {
                matrix[p][y] = 0;
              }
            }
          } else {
            if (matrix[p][x + 1]) {
              matrix[p][x + 1] = 0;
            } else {
              need_fill_col1 = true;
            }
          }
        }
      };
      if (x + 1 == m || x + 1 == n) {
        do_fill_row();
        do_fill_col();
        break;
      }
      need_fill_row1 = !matrix[x + 1][x + 1] || !matrix[x + 1][x];
      need_fill_col1 = !matrix[x + 1][x + 1] || !matrix[x][x + 1];
      last_fill_row1 = !matrix[x + 1][x];
      last_fill_col1 = !matrix[x][x + 1];
      propogate_row();
      propogate_col();
      do_fill_row();
      do_fill_col();
      need_fill_row = need_fill_row1;
      need_fill_col = need_fill_col1;
      last_fill_row = last_fill_row1;
      last_fill_col = last_fill_col1;
    }
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
