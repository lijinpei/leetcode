#include <vector>

class Solution {
  int n, m;
  std::vector<std::vector<char>>* grid;
  void search(int x, int y) {
    auto ok = [&](int x1, int y1) -> bool {
      return x1 >= 0 && x1 < n && y1 >= 0 && y1 < m && (*grid)[x1][y1] == '1';
    };
    auto my_try = [&](int x1, int y1) {
      if (ok(x1, y1)) {
        (*grid)[x1][y1] = '2';
        search(x1, y1);
      }
    };
    my_try(x + 1, y);
    my_try(x - 1, y);
    my_try(x, y + 1);
    my_try(x, y - 1);
  }
public:
  int numIslands(std::vector<std::vector<char>>& grid) {
    n = grid.size();
    m = n ? grid[0].size() : 0;
    if (!m) {
      return 0;
    }
    this->grid = &grid;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if ('1' == grid[i][j]) {
          grid[i][j] = '2';
          search(i, j);
          ++ans;
        }
      }
    }
    return ans;
  }
};
