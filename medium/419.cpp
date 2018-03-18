#include <vector>

class Solution {
public:
  int countBattleships(std::vector<std::vector<char>> &board) {
    int n = board.size();
    if (!n) {
      return 0;
    }
    int m = board[0].size();
    if (!m) {
      return 0;
    }
    int ans = 0;
    for (int i = 0, i1 = n - 1; i < i1; ++i) {
      for (int j = 0, j1 = m - 1; j < j1; ++j) {
        if ('X' == board[i][j] && '.' == board[i][j + 1] && '.' == board[i + 1][j]) {
          ++ans;
        }
      }
      if ('X' == board[i][m - 1] && '.' == board[i + 1][m - 1]) {
        ++ans;
      }
    }
    for (int j = 0, j1 = m - 1; j < j1; ++j) {
      if ('X' == board[n - 1][j] && '.' == board[n - 1][j + 1]) {
        ++ans;
      }
    }
    if ('X' == board[n - 1][m - 1]) {
      ++ans;
    }
    return ans;
  }
};
