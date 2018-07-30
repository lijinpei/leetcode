#include <iostream>
#include <vector>
#include <utility>

class Solution {
  class DFS {
    std::vector<std::vector<int>> &matrix;
    int n, m;
    std::vector<bool> flag;
    void run(int x, int y) {
      int h = matrix[x][y];
      auto try_visit = [&](int x1, int y1) {
        if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m) {
          return;
        }
        int p = x1 * m + y1;
        if (matrix[x1][y1] < h) {
          return;
        }
        if (flag[p]) {
          return;
        }
        flag[p] = true;
        run(x1, y1);
      };
      try_visit(x - 1, y);
      try_visit(x + 1, y);
      try_visit(x, y - 1);
      try_visit(x, y + 1);
    }
  public:
    DFS(std::vector<std::vector<int>> &matrix)
        : matrix(matrix), n(matrix.size()), m(matrix[0].size()), flag(n * m) {}
    bool visited(int x, int y) {
      return flag[x * m + y];
    }
    void visit(int x, int y) {
      int p = x * m + y;
      flag[p] = true;
      run(x, y);
    }
  };
public:
  std::vector<std::pair<int, int>> pacificAtlantic(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size(), m = n ? matrix[0].size() : 0;
    if (!m) {
      return {};
    }
    auto dfs1 = DFS(matrix);
    auto dfs2 = DFS(matrix);
    for (int x = 0; x < n; ++x) {
      dfs1.visit(x, 0);
      dfs2.visit(x, m - 1);
    }
    for (int y = 0; y < m; ++y) {
      dfs1.visit(0, y);
      dfs2.visit(n - 1, y);
    }
    std::vector<std::pair<int, int>> ret(n * m);
    ret.resize(0);
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        if (dfs1.visited(x, y) && dfs2.visited(x, y)) {
          ret.emplace_back(x, y);
        }
      }
    }
    /*
    std::cout << "dfs1:\n";
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        if (dfs1.visited(x, y)) {
          std::cout << x << ' ' << y << std::endl;
        }
      }
    }
    std::cout << "dfs2:\n";
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        if (dfs2.visited(x, y)) {
          std::cout << x << ' ' << y << std::endl;
        }
      }
    }
    */
    return ret;
  }
};

int main() {
  std::vector<int> v1 = {1,2,2,3,5};
  std::vector<int> v2 = {3,2,3,4,4};
  std::vector<int> v3 = {2,4,5,3,1};
  std::vector<int> v4 = {6,7,1,4,5};
  std::vector<int> v5 = {5,1,1,2,4};
  std::vector<std::vector<int>> input = {v1, v2, v3, v4, v5};
  Solution sol;
  auto ret = sol.pacificAtlantic(input);
  for (auto& r : ret) {
    std::cout << r.first << ' ' << r.second << std::endl;
  }
}
