#include <vector>
#include <string>

class Solution {
public:
  bool validTicTacToe(std::vector<std::string> &board) {
    auto count = [&](char ch) {
      int ret = 0;
      for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
          if (board[r][c] == ch) {
            ++ret;
          }
        }
      }
      return ret;
    };
    auto win_impl = [&](char ch) {
      for (int r = 0; r < 3; ++r) {
        bool same = true;
        for (int c = 0; c < 3; ++c) {
          if (board[r][c] != ch) {
            same = false;
            break;
          }
        }
        if (same) {
          return true;
        }
      }
      for (int r = 0; r < 3; ++r) {
        bool same = true;
        for (int c = 0; c < 3; ++c) {
          if (board[c][r] != ch) {
            same = false;
            break;
          }
        }
        if (same) {
          return true;
        }
      }
      bool same1 = true, same2 = true;
      for (int i = 0; i < 3; ++i) {
        if (board[i][i] != ch) {
          same1 = false;
        }
        if (board[i][2 - i] != ch) {
          same2 = false;
        }
      }
      return same1 || same2;
    };
    auto win = [&](char ch) -> std::pair<bool, bool> {
      if (!win_impl(ch)) {
        return {false, true};
      }
      for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
          if (board[r][c] != ch) {
            continue;
          }
          board[r][c] = ' ';
          bool not_win = win_impl(ch);
          board[r][c] = ch;
          if (!not_win) {
            return {true, true};
          }
        }
      }
      return {true, false};
    };
    int n1 = count('X');
    int n2 = count('O');
    auto r1 = win('X');
    auto r2 = win('O');
    if (!r1.second || !r2.second) {
      return false;
    }
    bool w1 = r1.first;
    bool w2 = r2.first;
    if (w1 && w2) {
      return false;
    }
    if (w2) {
      return n1 == n2;
    }
    if (w1) {
      return n1 == n2 + 1;
    }
    return n1 == n2 || n1 == n2 + 1;
  }
};
