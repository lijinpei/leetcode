#include <vector>

class Solution {
  using BoardTy = std::vector<std::vector<char>>;
  bool row[9][9], col[9][9], block[9][9];
  static int B(int i, int j) {
    i /= 3;
    j /= 3;
    return i * 3 + j;
  }
  static void fill_false(bool (&arr)[9][9]) {
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        arr[i][j] = false;
      }
    }
  }
  int init(BoardTy & board) {
    fill_false(row);
    fill_false(col);
    fill_false(block);
    int ret = 0;
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        int c = board[i][j] - '1';
        if (c >= 0 && c < 9) {
          ++ret;
        } else {
          continue;
        }
        row[i][c] = true;
        col[j][c] = true;
        block[B(i, j)][c] = true;
      }
    }
    return ret;
  }
  int getFreeDom(int x, int y) {
    int b = B(x, y);
    int ret = 0;
    for (int i = 0; i < 9; ++i) {
      if (!(row[x][i] || col[y][i] || block[b][i])) {
        ++ret;
      }
    }
    return ret;
  }
  int minFreedomPos(BoardTy & board, int & x, int & y) {
    int mf = 10;
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        char c = board[i][j];
        if (!(c == '.')) {
          continue;
        }
        int nmf = getFreeDom(i, j);
        if (!nmf) {
          return -1;
        }
        if (nmf < mf) {
          mf = nmf;
          x = i;
          y = j;
        }
      }
    }
    return mf;
  }
  bool search(BoardTy & board, int n) {
    if (n == 81) {
      return true;
    }
    int x, y;
    int pos = minFreedomPos(board, x, y);
    if (pos <= 0) {
      return false;
    }
    int b = B(x, y);
    for (int i = 0; i < 9; ++i) {
      if (!row[x][i] && !col[y][i] && !block[b][i]) {
        board[x][y] = '1' + i;
        row[x][i] = true;
        col[y][i] = true;
        block[b][i] = true;
        if (search(board, n + 1)) {
          return true;
        }
        board[x][y] = '.';
        row[x][i] = false;
        col[y][i] = false;
        block[b][i] = false;
      }
    }
    return false;
  }
public:
  void solveSudoku(std::vector<std::vector<char>> &board) {
    int n = init(board);
    search(board, n);
  }
};
