#include <iostream>
#include <vector>
#include <tuple>

class Solution {
public:
  void solve(std::vector<std::vector<char>> &board) {
    int n = board.size();
    if (!n) {
      return;
    }
    int m = board[0].size();
    if (!m) {
      return;
    }
    std::vector<std::tuple<int, int, int>> stack(n * m);
    auto fill = [&](int x, int y) {
      int dx[] = {1, -1, 0, 0};
      int dy[] = {0, 0, 1, -1};
      stack[0] = {x, y, 0};
      int tos = 1;
      auto mytry = [&](int nx, int ny) {
        if (nx < 0 || nx >= n || ny < 0 || ny >= m || board[nx][ny] != 'O') {
          return false;
        }
        board[nx][ny] = '\0';
        stack[tos++] = {nx, ny, 0};
        return true;
      };
      board[x][y] = '\0';
      while (tos) {
        x = std::get<0>(stack[tos - 1]);
        y = std::get<1>(stack[tos - 1]);
        int& k = std::get<2>(stack[tos - 1]);
        bool b = false;
        while (k < 4) {
          b = mytry(x + dx[k], y + dy[k]);
          ++k;
          if (b || k == 4) {
            break;
          }
        }
        if (b) {
          continue;
        } else {
          --tos;
        }
      }
    };
    for (int i = 0; i < n; ++i) {
      if (board[i][0] == 'O') {
        board[i][0] = '\0';
        fill(i, 0);
      }
      if (board[i][m - 1] == 'O') {
        board[i][m - 1] = '\0';
        fill(i, m - 1);
      }
    }
    for (int i = 0; i < m; ++i) {
      if (board[0][i] == 'O') {
        board[0][i] = '\0';
        fill(0, i);
      }
      if (board[n - 1][i] == 'O') {
        board[n - 1][i] = '\0';
        fill(n - 1, i);
      }
    }
    for (auto & v : board) {
      for (auto & c : v) {
        c = (c == '\0' ? 'O' : 'X');
      }
    }
  }
};

int main() {
  Solution sol;
  std::vector<std::vector<char>> v = {{'X', 'O', 'X'}, {'X', 'O', 'X'}, {'X', 'O', 'X'}};
  sol.solve(v);
}
