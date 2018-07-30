#include <string>
#include <vector>

class Solution {
  class SolutionImpl {
    std::vector<std::vector<char>> &board;
    const std::string &word;
    int n, m, s;
    std::vector<std::vector<int>> flag;
    int epoch;

    bool search(int x, int y, int l) {
      const int dx[] = {1, -1, 0, 0};
      const int dy[] = {0, 0, 1, -1};
      if (l == s) {
        return true;
      }

      flag[x][y] = epoch;
      auto ok = [&](int nx, int ny) {
        return nx >= 0 && nx < n && ny >= 0 && ny < m &&
               board[nx][ny] == word[l] && flag[nx][ny] != epoch;
      };
      for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (ok(nx, ny) && search(nx, ny, l + 1)) {
          return true;
        }
      }
      flag[x][y] = 0;
      return false;
    }

  public:
    SolutionImpl(std::vector<std::vector<char>> &b, const std::string &w)
        : board(b), word(w), n(board.size()), m(n ? board[0].size() : 0),
          s(word.size()), flag(n, std::vector<int>(m)) {}

    bool run() {
      if (!m) {
        return false;
      }
      if (!s) {
        return true;
      }
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          ++epoch;
          if (board[i][j] == word[0] && search(i, j, 1)) {
            return true;
          }
        }
      }
      return false;
    }
  };

public:
  bool exist(std::vector<std::vector<char>> &board, const std::string &word) {
    return SolutionImpl(board, word).run();
  }
};

int main() { Solution sol; }
