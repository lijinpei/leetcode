#include <vector>

class Solution {
public:
  int largestIsland(std::vector<std::vector<int>> &grid) {
    int n = grid.size();
    int m = n ? grid[0].size() : 0;
    if (!m) {
      return 0;
    }
    std::vector<int> count(n * m + 2);
    std::vector<std::pair<int, int>> queue(n * m);
    auto fill = [&](int r, int c, int flag) {
      int head = 0, tail = 1;
      queue[0] = {r, c};
      grid[r][c] = flag;
      auto try_enqueue = [&](int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= m) {
          return;
        }
        if (grid[r][c] != 1) {
          return;
        }
        grid[r][c] = flag;
        queue[tail++] = {r, c};
        return;
      };
      while (head < tail) {
        int r = queue[head].first;
        int c = queue[head].second;
        ++head;
        try_enqueue(r, c + 1);
        try_enqueue(r, c - 1);
        try_enqueue(r + 1, c);
        try_enqueue(r - 1, c);
      }
      return tail;
    };
    int flag = 2;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] == 1) {
          int nv = fill(i, j, flag);
          count[flag] = nv;
          if (nv > ans) {
            ans = nv;
          }
          ++flag;
        }
      }
    }
    auto area = [&](int r, int c) {
      if (r < 0 || r >= n || c < 0 || c >= m) {
        return 0;
      }
      return grid[r][c];
    };
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (grid[i][j]) {
          continue;
        }
        int arr[] = {area(i, j + 1), area(i, j - 1), area(i + 1, j),
                     area(i - 1, j)};
        for (int i = 1; i < 4; ++i) {
          for (int j = 0; j < i; ++j) {
            if (arr[i] == arr[j]) {
              arr[j] = 0;
              break;
            }
          }
        }
        int nv = 1;
        for (int i = 0; i < 4; ++i) {
          nv += count[arr[i]];
        }
        if (nv > ans) {
          ans = nv;
        }
      }
    }
    return ans;
  }
};

