#include <vector>

using BoardTy = std::vector<std::vector<int>>;

class LongestIncreasingPathImpl {
  int N, M;
  const BoardTy & matrix;
  BoardTy path;
  int dfs(int x, int y) {
    if (path[x][y]) {
      return path[x][y];
    }
    int h = matrix[x][y];
    int d = 0;
    if (x && matrix[x - 1][y] > h) {
      d = dfs(x - 1, y);
    }
    if (x + 1 < N && matrix[x + 1][y] > h) {
      d = std::max(d, dfs(x + 1, y));
    }
    if (y && matrix[x][y - 1] > h) {
      d = std::max(d, dfs(x, y - 1));
    }
    if (y + 1 < M && matrix[x][y + 1] > h) {
      d = std::max(d, dfs(x, y + 1));
    }
    return path[x][y] = d + 1;
  }
public:
  LongestIncreasingPathImpl(int n, int m, const BoardTy & matrix) : N(n), M(m), matrix(matrix), path(n, std::vector<int>(m, 0)) {}
  int solve() {
    auto ret = 0;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        ret = std::max(ret, dfs(i, j));
      }
    }
    return ret;
  }
};

class Solution {
public:
  int longestIncreasingPath(BoardTy & matrix) {
    int n = matrix.size();
    int m = n ? matrix[0].size() : 0;
    return m ? LongestIncreasingPathImpl(n, m, matrix).solve() : 0;
  }
};
